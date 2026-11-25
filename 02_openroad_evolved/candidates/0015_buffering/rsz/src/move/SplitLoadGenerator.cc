// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SplitLoadGenerator.hh"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "SplitLoadCandidate.hh"
#include "db_sta/dbNetwork.hh"
#include "db_sta/dbSta.hh"
#include "odb/db.h"
#include "odb/geom.h"
#include "rsz/Resizer.hh"
#include "sta/Delay.hh"
#include "sta/Graph.hh"
#include "sta/GraphClass.hh"
#include "sta/Liberty.hh"
#include "sta/Network.hh"
#include "sta/NetworkClass.hh"
#include "sta/Path.hh"
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
    debugPrint(resizer.logger(),
               RSZ,
               "split_load_move",
               2,
               "REJECT SplitLoadMove {}: Fanout {} <= {} min fanout",
               resizer.network()->pathName(drvr_pin),
               target.fanout,
               kSplitLoadMinFanout);
    return false;
  }
  if (!resizer.okToBufferNet(drvr_pin)) {
    debugPrint(resizer.logger(),
               RSZ,
               "split_load_move",
               2,
               "REJECT SplitLoadMove {}: Not OK to buffer net",
               resizer.network()->pathName(drvr_pin));
    return false;
  }

  drvr_vertex = target.vertex(resizer);
  return drvr_vertex != nullptr;
}

std::vector<FanoutSlack> collectRankedFanoutSlacks(Resizer& resizer,
                                                   const Target& target,
                                                   sta::Vertex* drvr_vertex,
                                                   sta::Slack& drvr_slack_out)
{
  std::vector<FanoutSlack> fanout_slacks;
  const sta::Path* driver_path = target.driverPath(resizer);
  const sta::RiseFall* rf = driver_path != nullptr
                                ? driver_path->transition(resizer.staState())
                                : nullptr;
  if (rf == nullptr) {
    return fanout_slacks;
  }

  const sta::Slack drvr_slack
      = resizer.sta()->slack(drvr_vertex, resizer.maxAnalysisMode());
  drvr_slack_out = drvr_slack;
  sta::VertexOutEdgeIterator edge_iter(drvr_vertex, resizer.graph());
  while (edge_iter.hasNext()) {
    sta::Edge* edge = edge_iter.next();
    if (!edge->isWire()) {
      continue;
    }

    sta::Vertex* fanout_vertex = edge->to(resizer.graph());
    const sta::Slack fanout_slack
        = resizer.sta()->slack(fanout_vertex, rf, resizer.maxAnalysisMode());
    fanout_slacks.emplace_back(fanout_vertex, fanout_slack - drvr_slack);
  }

  std::ranges::sort(fanout_slacks,
                    [&resizer](const FanoutSlack& lhs, const FanoutSlack& rhs) {
                      return lhs.second > rhs.second
                             || (lhs.second == rhs.second
                                 && resizer.network()->pathNameLess(
                                     lhs.first->pin(), rhs.first->pin()));
                    });
  return fanout_slacks;
}

std::unique_ptr<sta::PinSet> makeLoadSet(
    Resizer& resizer,
    const std::vector<FanoutSlack>& fanout_slacks,
    const int moved_count)
{
  auto load_pins = std::make_unique<sta::PinSet>(resizer.network());
  for (int i = 0; i < moved_count; ++i) {
    sta::Pin* split_pin = fanout_slacks[i].first->pin();
    if (!resizer.network()->isTopLevelPort(split_pin)) {
      load_pins->insert(split_pin);
    }
  }
  return load_pins;
}

// Evolved: TNS-weighted critical-sink isolation.  The stock recipe always
// moves the less critical half of the sinks behind a buffer.  Here several
// cut points (number of critical sinks kept on the driver) are scored with a
// first-order model: moving capacitance Cm off the driver speeds every kept
// sink up by g = Rdrv * (Cm - Cbuf) and every moved sink by g - bufferDelay.
// Each sink is weighted by its own negative slack (TNS contribution).
struct CutPlan
{
  int moved{0};
  bool feasible{false};
  float d_tns{0.0f};
  float new_worst{0.0f};
};

// Returns moved-sink counts in order of preference.
std::vector<int> rankCutPoints(Resizer& resizer,
                               const std::vector<FanoutSlack>& fanout_slacks,
                               const sta::Slack drvr_slack,
                               const sta::Pin* drvr_pin,
                               sta::LibertyCell* buffer_cell)
{
  const int n = static_cast<int>(fanout_slacks.size());
  const int stock_moved = n / 2;
  std::vector<int> order{stock_moved};
  if (n < 4 || buffer_cell == nullptr) {
    return order;
  }

  const sta::Scene* scene = resizer.sta()->cmdScene();
  const sta::MinMax* min_max = resizer.maxAnalysisMode();
  sta::LibertyPort* buf_in = nullptr;
  sta::LibertyPort* buf_out = nullptr;
  buffer_cell->bufferPorts(buf_in, buf_out);
  const float rdrv = resizer.driveResistance(drvr_pin);
  if (rdrv <= 0.0f || buf_in == nullptr) {
    return order;
  }
  const float cbuf = resizer.portCapacitance(buf_in, scene);

  std::vector<float> slack(n);
  std::vector<float> cap(n, 0.0f);
  int neg_count = 0;
  for (int i = 0; i < n; ++i) {
    slack[i] = static_cast<float>(drvr_slack)
               + static_cast<float>(fanout_slacks[i].second);
    if (slack[i] < 0.0f) {
      ++neg_count;
    }
    const sta::Pin* pin = fanout_slacks[i].first->pin();
    sta::LibertyPort* port = resizer.network()->libertyPort(pin);
    if (port != nullptr) {
      cap[i] = resizer.portCapacitance(port, scene);
    }
  }
  const float base_worst = *std::ranges::min_element(slack);

  // Candidate numbers of critical sinks kept on the driver.
  const int keeps[] = {neg_count, n / 4, n - stock_moved, (3 * n) / 4};
  std::vector<int> moved_counts;
  for (const int raw_keep : keeps) {
    const int keep = std::clamp(raw_keep, 1, n - 1);
    const int moved = n - keep;
    if (std::ranges::find(moved_counts, moved) == moved_counts.end()) {
      moved_counts.push_back(moved);
    }
  }

  std::vector<CutPlan> plans;
  for (const int moved : moved_counts) {
    float cm = 0.0f;
    for (int i = 0; i < moved; ++i) {
      cm += cap[i];
    }
    CutPlan plan;
    plan.moved = moved;
    const float gain = rdrv * (cm - cbuf);
    if (cm > 0.0f && gain > 0.0f) {
      const float buf_delay
          = resizer.bufferDelay(buffer_cell, cm, scene, min_max);
      float worst = slack[0] + gain - buf_delay;
      float d_tns = 0.0f;
      for (int i = 0; i < n; ++i) {
        const float delta = i < moved ? gain - buf_delay : gain;
        const float after = slack[i] + delta;
        worst = std::min(worst, after);
        d_tns += std::min(0.0f, after) - std::min(0.0f, slack[i]);
      }
      plan.new_worst = worst;
      plan.d_tns = d_tns;
      plan.feasible = worst >= base_worst;
    }
    plans.push_back(plan);
  }

  std::ranges::stable_sort(plans, [](const CutPlan& a, const CutPlan& b) {
    if (a.feasible != b.feasible) {
      return a.feasible;
    }
    if (a.d_tns != b.d_tns) {
      return a.d_tns > b.d_tns;
    }
    return a.new_worst > b.new_worst;
  });

  order.clear();
  for (const CutPlan& plan : plans) {
    if (plan.feasible) {
      order.push_back(plan.moved);
    }
  }
  if (std::ranges::find(order, stock_moved) == order.end()) {
    order.push_back(stock_moved);  // stock recipe stays as last resort
  }
  return order;
}

// Counters, reported once when the last generator is destroyed.
int64_t g_cutpoint_reranked = 0;
int64_t g_cutpoint_candidates = 0;
int64_t g_cutpoint_dropped = 0;
int g_live_generators = 0;

}  // namespace

SplitLoadGenerator::SplitLoadGenerator(const GeneratorContext& context)
    : MoveGenerator(context)
{
  ++g_live_generators;
}

SplitLoadGenerator::~SplitLoadGenerator()
{
  if (--g_live_generators == 0) {
    utl::Logger* logger = resizer_.logger();
    logger->report("RSZ_EVOLVE split_cutpoint_reranked fired={}",
                   g_cutpoint_reranked);
    logger->report("RSZ_EVOLVE split_cutpoint_candidates fired={}",
                   g_cutpoint_candidates);
    logger->report("RSZ_EVOLVE split_cutpoint_dropped fired={}",
                   g_cutpoint_dropped);
    g_cutpoint_reranked = 0;
    g_cutpoint_candidates = 0;
    g_cutpoint_dropped = 0;
  }
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

  sta::Slack drvr_slack = 0.0;
  std::vector<FanoutSlack> fanout_slacks
      = collectRankedFanoutSlacks(resizer_, target, drvr_vertex, drvr_slack);
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

  const std::vector<int> cut_order = rankCutPoints(
      resizer_, fanout_slacks, drvr_slack, drvr_pin, buffer_cell);
  const int stock_moved = static_cast<int>(fanout_slacks.size()) / 2;
  if (cut_order.front() != stock_moved) {
    ++g_cutpoint_reranked;
  }

  const odb::Point drvr_loc = resizer_.dbNetwork()->location(drvr_pin);
  for (const int moved : cut_order) {
    std::unique_ptr<sta::PinSet> load_pins
        = makeLoadSet(resizer_, fanout_slacks, moved);
    if (load_pins->empty()) {
      ++g_cutpoint_dropped;
      continue;
    }
    ++g_cutpoint_candidates;
    candidates.push_back(std::make_unique<SplitLoadCandidate>(
        resizer_,
        target,
        drvr_net,
        buffer_cell,
        drvr_loc,
        std::move(load_pins)));
  }
  return candidates;
}

}  // namespace rsz
