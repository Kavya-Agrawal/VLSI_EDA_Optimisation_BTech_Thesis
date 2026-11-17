// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SplitLoadGenerator.hh"

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "SplitLoadCandidate.hh"
#include "db_sta/dbNetwork.hh"
#include "db_sta/dbSta.hh"
#include "est/EstimateParasitics.h"
#include "odb/db.h"
#include "odb/geom.h"
#include "rsz/Resizer.hh"
#include "sta/Delay.hh"
#include "sta/Graph.hh"
#include "sta/GraphClass.hh"
#include "sta/GraphDelayCalc.hh"
#include "sta/Liberty.hh"
#include "sta/Network.hh"
#include "sta/NetworkClass.hh"
#include "sta/Path.hh"
#include "sta/Scene.hh"
#include "sta/Transition.hh"
#include "utl/Logger.h"

namespace rsz {

using utl::RSZ;

namespace {

constexpr int kSplitLoadMinFanout = 8;
using FanoutSlack = std::pair<sta::Vertex*, sta::Slack>;

bool resolveDriverPin(Resizer& resizer,
                      const Target& target,
                      sta::Pin*& drvr_pin,
                      sta::Vertex*& drvr_vertex)
{
  if (!target.canBePathDriver()) {
    return false;
  }

  drvr_pin = target.resolvedPin(resizer);
  if (drvr_pin == nullptr) {
    return false;
  }
  if (target.fanout <= kSplitLoadMinFanout) {
    debugPrint(resizer.logger(), RSZ, "split_load_move", 2,
               "REJECT SplitLoadMove {}: Fanout {} <= {} min fanout",
               resizer.network()->pathName(drvr_pin), target.fanout,
               kSplitLoadMinFanout);
    return false;
  }
  if (!resizer.okToBufferNet(drvr_pin)) {
    debugPrint(resizer.logger(), RSZ, "split_load_move", 2,
               "REJECT SplitLoadMove {}: Not OK to buffer net",
               resizer.network()->pathName(drvr_pin));
    return false;
  }

  drvr_vertex = target.vertex(resizer);
  return drvr_vertex != nullptr;
}

std::vector<FanoutSlack> collectRankedFanoutSlacks(Resizer& resizer,
                                                   const Target& target,
                                                   sta::Vertex* drvr_vertex)
{
  std::vector<FanoutSlack> fanout_slacks;
  const sta::Path* driver_path = target.driverPath(resizer);
  const sta::RiseFall* rf = driver_path != nullptr
                                ? driver_path->transition(resizer.staState())
                                : nullptr;
  if (rf == nullptr) {
    return fanout_slacks;
  }

  const sta::Slack drvr_slack =
      resizer.sta()->slack(drvr_vertex, resizer.maxAnalysisMode());
  sta::VertexOutEdgeIterator edge_iter(drvr_vertex, resizer.graph());
  while (edge_iter.hasNext()) {
    sta::Edge* edge = edge_iter.next();
    if (!edge->isWire()) {
      continue;
    }

    sta::Vertex* fanout_vertex = edge->to(resizer.graph());
    const sta::Slack fanout_slack =
        resizer.sta()->slack(fanout_vertex, rf, resizer.maxAnalysisMode());
    fanout_slacks.emplace_back(fanout_vertex, fanout_slack - drvr_slack);
  }

  std::ranges::sort(fanout_slacks, [&resizer](const FanoutSlack& lhs,
                                              const FanoutSlack& rhs) {
    return lhs.second > rhs.second || (lhs.second == rhs.second &&
                                       resizer.network()->pathNameLess(
                                           lhs.first->pin(), rhs.first->pin()));
  });
  return fanout_slacks;
}

// Keep the existing headroom order, but spend each branch's slack budget
// rather than moving a fixed number of sinks.  No trial netlist edits are
// needed: application still uses the journaled SplitLoadCandidate.
std::unique_ptr<sta::PinSet> chooseSplitLoads(
    Resizer& resizer,
    const Target& target,
    sta::Pin* drvr_pin,
    sta::LibertyCell* buffer_cell,
    const std::vector<FanoutSlack>& fanout_slacks)
{
  auto best_pins = std::make_unique<sta::PinSet>(resizer.network());
  const auto* scene = target.activeScene(resizer);
  const auto* min_max = target.minMax(resizer);
  const auto* driver_port = resizer.network()->libertyPort(drvr_pin);
  // Without the captured path load we cannot guarantee path retention.
  if (scene == nullptr || min_max == nullptr || driver_port == nullptr ||
      target.load_pin == nullptr ||
      !std::ranges::any_of(fanout_slacks, [&target](const auto& load) {
        return load.first->pin() == target.load_pin;
      })) {
    return best_pins;
  }
  driver_port = driver_port->scenePort(scene->libertyIndex(min_max));
  if (driver_port == nullptr) {
    return best_pins;
  }

  const odb::Point origin = resizer.dbNetwork()->location(drvr_pin);
  odb::Rect all_box(origin, origin);
  for (const auto& [vertex, headroom] : fanout_slacks) {
    all_box.merge(resizer.dbNetwork()->location(vertex->pin()));
  }
  double wire_res = 0.0;
  double wire_cap = 0.0;
  resizer.estimateParasitics()->wireSignalRC(scene, wire_res, wire_cap);
  const double cap_per_dbu = wire_cap * resizer.dbuToMeters(1);
  const float old_cap =
      resizer.sta()->graphDelayCalc()->loadCap(drvr_pin, scene, min_max);
  sta::ArcDelay old_delay[sta::RiseFall::index_count];
  sta::Slew old_slew[sta::RiseFall::index_count];
  resizer.gateDelays(driver_port, old_cap, scene, min_max, old_delay, old_slew);

  sta::PinSet moved(resizer.network());
  float moved_cap = 0.0f;
  odb::Rect moved_box(origin, origin);
  float best_gain = 0.0f;
  double best_tns_gain = 0.0;
  for (size_t prefix = 0; prefix < fanout_slacks.size(); ++prefix) {
    sta::Pin* pin = fanout_slacks[prefix].first->pin();
    if (pin == target.load_pin || resizer.network()->isTopLevelPort(pin)) {
      continue;
    }
    const auto* port = resizer.network()->libertyPort(pin);
    port = port != nullptr ? port->scenePort(scene->libertyIndex(min_max))
                           : nullptr;
    if (port == nullptr) {
      // A prefix with an unmodelled load cannot be evaluated safely.
      break;
    }
    moved.insert(pin);
    moved_cap += port->capacitance();
    moved_box.merge(resizer.dbNetwork()->location(pin));
    if (moved.size() >= fanout_slacks.size()) {
      break;
    }

    odb::Rect kept_box(origin, origin);
    for (const auto& [vertex, headroom] : fanout_slacks) {
      if (moved.find(vertex->pin()) == moved.end()) {
        kept_box.merge(resizer.dbNetwork()->location(vertex->pin()));
      }
    }
    // HPWL approximates the two new nets, both rooted at the driver.
    const float branch_cap =
        moved_cap + cap_per_dbu * (moved_box.dx() + moved_box.dy());
    const float saved_wire_cap = cap_per_dbu * (all_box.dx() + all_box.dy() -
                                                kept_box.dx() - kept_box.dy());
    auto* sized_cell = resizer.findTargetCell(buffer_cell, branch_cap, false);
    auto* scene_cell =
        sized_cell != nullptr ? sized_cell->sceneCell(scene, min_max) : nullptr;
    sta::LibertyPort *input = nullptr, *output = nullptr;
    if (scene_cell != nullptr) {
      scene_cell->bufferPorts(input, output);
    }
    if (input == nullptr || output == nullptr) {
      continue;
    }
    const float new_cap = std::max(
        0.0f, old_cap - moved_cap - saved_wire_cap + input->capacitance());
    sta::ArcDelay new_delay[sta::RiseFall::index_count];
    sta::Slew new_slew[sta::RiseFall::index_count];
    sta::ArcDelay buffer_delay[sta::RiseFall::index_count];
    sta::Slew buffer_slew[sta::RiseFall::index_count];
    resizer.gateDelays(driver_port, new_cap, scene, min_max, new_delay,
                       new_slew);
    resizer.gateDelays(output, branch_cap, new_slew, scene, min_max,
                       buffer_delay, buffer_slew);

    bool safe = true;
    float old_worst = std::numeric_limits<float>::infinity();
    float new_worst = std::numeric_limits<float>::infinity();
    double tns_gain = 0.0;
    for (const auto& [vertex, headroom] : fanout_slacks) {
      const bool is_moved = moved.find(vertex->pin()) != moved.end();
      for (const auto* rf : sta::RiseFall::range()) {
        const int index = rf->index();
        const auto slack =
            resizer.sta()->slack(vertex, rf, resizer.maxAnalysisMode());
        if (sta::delayInf(slack, resizer.sta())) {
          continue;
        }
        const float change =
            sta::delayAsFloat(new_delay[index]) -
            sta::delayAsFloat(old_delay[index]) +
            (is_moved ? sta::delayAsFloat(buffer_delay[index]) : 0.0f);
        const float before = sta::delayAsFloat(slack);
        const float after = before - change;
        if (!std::isfinite(change) || old_delay[index] <= -sta::INF ||
            new_delay[index] <= -sta::INF || buffer_delay[index] <= -sta::INF ||
            (is_moved && ((before < 0.0f && after < before) ||
                          (before >= 0.0f && after < 0.0f)))) {
          safe = false;
        }
        old_worst = std::min(old_worst, before);
        new_worst = std::min(new_worst, after);
        tns_gain += std::min(after, 0.0f) - std::min(before, 0.0f);
      }
    }
    const float gain = new_worst - old_worst;
    if (safe && std::isfinite(gain) && gain > 0.0f &&
        (gain > best_gain || (gain == best_gain && tns_gain > best_tns_gain))) {
      best_gain = gain;
      best_tns_gain = tns_gain;
      *best_pins = moved;
    }
  }
  debugPrint(
      resizer.logger(), RSZ, "split_load_move", 2,
      "SplitLoadMove {}: selected {} loads, predicted worst slack gain {} "
      "aggregate negative slack gain {}",
      resizer.network()->pathName(drvr_pin), best_pins->size(), best_gain,
      best_tns_gain);
  return best_pins;
}

}  // namespace

SplitLoadGenerator::SplitLoadGenerator(const GeneratorContext& context)
    : MoveGenerator(context)
{
}

std::vector<std::unique_ptr<MoveCandidate>> SplitLoadGenerator::generate(
    const Target& target)
{
  std::vector<std::unique_ptr<MoveCandidate>> candidates;
  sta::Pin* drvr_pin = nullptr;
  sta::Vertex* drvr_vertex = nullptr;
  if (!resolveDriverPin(resizer_, target, drvr_pin, drvr_vertex)) {
    return candidates;
  }

  std::vector<FanoutSlack> fanout_slacks =
      collectRankedFanoutSlacks(resizer_, target, drvr_vertex);
  if (fanout_slacks.empty()) {
    return candidates;
  }

  sta::LibertyCell* buffer_cell = resizer_.lowestDriveBufferCell();
  odb::dbNet* db_drvr_net = nullptr;
  odb::dbModNet* db_mod_drvr_net = nullptr;
  resizer_.dbNetwork()->net(drvr_pin, db_drvr_net, db_mod_drvr_net);
  sta::Net* drvr_net = resizer_.dbNetwork()->dbToSta(db_drvr_net);
  if (buffer_cell == nullptr || drvr_net == nullptr) {
    return candidates;
  }

  std::unique_ptr<sta::PinSet> load_pins =
      chooseSplitLoads(resizer_, target, drvr_pin, buffer_cell, fanout_slacks);
  if (load_pins->empty()) {
    return candidates;
  }

  const odb::Point drvr_loc = resizer_.dbNetwork()->location(drvr_pin);
  candidates.push_back(std::make_unique<SplitLoadCandidate>(
      resizer_, target, drvr_net, buffer_cell, drvr_loc, std::move(load_pins)));
  return candidates;
}

}  // namespace rsz
