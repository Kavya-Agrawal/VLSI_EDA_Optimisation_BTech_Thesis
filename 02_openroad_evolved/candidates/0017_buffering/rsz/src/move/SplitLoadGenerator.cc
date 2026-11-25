// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SplitLoadGenerator.hh"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
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

  const sta::Slack drvr_slack
      = resizer.sta()->slack(drvr_vertex, resizer.maxAnalysisMode());
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

std::unique_ptr<sta::PinSet> chooseSplitLoads(
    Resizer& resizer,
    const std::vector<FanoutSlack>& fanout_slacks)
{
  auto load_pins = std::make_unique<sta::PinSet>(resizer.network());
  const int split_index = fanout_slacks.size() / 2;
  for (int i = 0; i < split_index; ++i) {
    sta::Pin* split_pin = fanout_slacks[i].first->pin();
    if (!resizer.network()->isTopLevelPort(split_pin)) {
      load_pins->insert(split_pin);
    }
  }
  return load_pins;
}

// Required-time-ordered (LT-tree) fanout synthesis for shared high-fanout
// drivers.  Nets below kTreeMinFanout keep the stock half-split move.
constexpr int kTreeMinFanout = 40;
constexpr int kTreeMaxGroups = 4;
constexpr float kTreeMinGain = 1e-12f;  // predicted min-slack gain, seconds
constexpr float kDirectCapFractions[] = {0.03f, 0.08f, 0.15f, 0.30f};

struct TreeSink
{
  sta::Pin* pin;
  float cap;
  float rel_slack;  // slack relative to the driver, most critical first
  odb::Point loc;
  bool is_port;
};

struct BufferModel
{
  sta::LibertyCell* cell;
  float cin;
  float res;
  float intrinsic;
  float max_cap;
};

struct TreePlan
{
  std::vector<int> group_begin;  // indices into sinks, size = groups + 1
  std::vector<int> group_buf;    // buffer model index per group
  size_t direct_count{0};
  float score{-1e30f};
};

std::vector<BufferModel> buildBufferModels(Resizer& resizer)
{
  sta::LibertyCellSeq cells;
  resizer.getBufferList(cells);
  std::ranges::sort(cells, [](const sta::LibertyCell* a, const sta::LibertyCell* b) {
    return std::string_view(a->name()) < std::string_view(b->name());
  });
  std::vector<BufferModel> models;
  for (sta::LibertyCell* cell : cells) {
    if (resizer.dontUse(cell)) {
      continue;
    }
    sta::LibertyPort *input, *output;
    cell->bufferPorts(input, output);
    if (input == nullptr || output == nullptr) {
      continue;
    }
    float max_cap = 0.0f;
    bool has_limit = false;
    output->capacitanceLimit(sta::MinMax::max(), max_cap, has_limit);
    models.push_back({cell,
                      input->capacitance(),
                      output->driveResistance(),
                      sta::delayAsFloat(output->intrinsicDelay(resizer.staState())),
                      has_limit ? max_cap : 1e30f});
  }
  return models;
}

// Pick the buffer minimising delay of the group plus the driver-side cost of
// its input pin; returns -1 when no buffer respects the max-cap limit.
int bestBufferForGroup(const std::vector<BufferModel>& models,
                       const float group_cap,
                       const float drvr_res)
{
  int best = -1;
  float best_cost = 1e30f;
  for (size_t i = 0; i < models.size(); ++i) {
    const BufferModel& m = models[i];
    if (group_cap > 0.9f * m.max_cap) {
      continue;
    }
    const float cost
        = m.intrinsic + m.res * group_cap + drvr_res * m.cin;
    if (cost < best_cost) {
      best_cost = cost;
      best = static_cast<int>(i);
    }
  }
  return best;
}

// Evaluate one (direct fraction, group count) variant with a lumped model:
// removing C_off of load from the driver speeds every direct sink by
// R_drvr * (C_off - sum Cin); every buffered group pays buffer delay.
TreePlan evaluateVariant(const std::vector<TreeSink>& sinks,
                         const std::vector<BufferModel>& models,
                         const float drvr_res,
                         const float total_cap,
                         const float direct_fraction,
                         const int num_groups)
{
  TreePlan plan;
  size_t direct = 0;
  float direct_cap = 0.0f;
  while (direct < sinks.size()
         && (sinks[direct].is_port || direct == 0
             || direct_cap < direct_fraction * total_cap)) {
    direct_cap += sinks[direct].cap;
    ++direct;
  }
  // Ports further down the order also stay on the driver.
  if (direct >= sinks.size()) {
    return plan;
  }
  float rest_cap = 0.0f;
  for (size_t i = direct; i < sinks.size(); ++i) {
    if (!sinks[i].is_port) {
      rest_cap += sinks[i].cap;
    }
  }
  if (rest_cap <= 0.0f) {
    return plan;
  }
  plan.direct_count = direct;
  plan.group_begin.push_back(static_cast<int>(direct));
  const float target_cap = rest_cap / static_cast<float>(num_groups);
  float acc = 0.0f;
  float group_cap = 0.0f;
  std::vector<float> group_caps;
  std::vector<float> group_slack;
  float group_min = 1e30f;
  for (size_t i = direct; i < sinks.size(); ++i) {
    if (sinks[i].is_port) {
      continue;
    }
    group_cap += sinks[i].cap;
    group_min = std::min(group_min, sinks[i].rel_slack);
    acc += sinks[i].cap;
    const bool close_group
        = static_cast<int>(group_caps.size()) + 1 < num_groups
          && acc >= target_cap * static_cast<float>(group_caps.size() + 1);
    if (close_group) {
      group_caps.push_back(group_cap);
      group_slack.push_back(group_min);
      plan.group_begin.push_back(static_cast<int>(i + 1));
      group_cap = 0.0f;
      group_min = 1e30f;
    }
  }
  if (group_cap > 0.0f) {
    group_caps.push_back(group_cap);
    group_slack.push_back(group_min);
    plan.group_begin.push_back(static_cast<int>(sinks.size()));
  }
  if (group_caps.empty()) {
    return plan;
  }
  float buf_cin = 0.0f;
  for (const float gc : group_caps) {
    const int b = bestBufferForGroup(models, gc, drvr_res);
    if (b < 0) {
      plan.score = -1e30f;
      return plan;
    }
    plan.group_buf.push_back(b);
    buf_cin += models[b].cin;
  }
  const float gain = drvr_res * (rest_cap - buf_cin);
  // Direct sinks keep their relative slack and gain from the lighter load.
  float worst = sinks.front().rel_slack + gain;
  for (size_t g = 0; g < group_caps.size(); ++g) {
    const BufferModel& m = models[plan.group_buf[g]];
    const float delay = m.intrinsic + m.res * group_caps[g];
    worst = std::min(worst, group_slack[g] + gain - delay);
  }
  plan.score = worst - sinks.front().rel_slack;
  return plan;
}

}  // namespace

SplitLoadGenerator::SplitLoadGenerator(const GeneratorContext& context)
    : MoveGenerator(context)
{
}

SplitLoadGenerator::~SplitLoadGenerator()
{
  FanoutTreeStats& stats = fanoutTreeStats();
  utl::Logger* logger = resizer_.logger();
  logger->report("RSZ_EVOLVE fanout_tree_built fired={}", stats.trees_built);
  logger->report("RSZ_EVOLVE fanout_tree_buffers fired={}",
                 stats.buffers_inserted);
  logger->report("RSZ_EVOLVE fanout_tree_sinks_isolated fired={}",
                 stats.sinks_isolated);
  logger->report("RSZ_EVOLVE fanout_tree_stock_fallback fired={}",
                 stats.stock_fallback);
  stats = FanoutTreeStats{};
}

static std::vector<std::unique_ptr<MoveCandidate>> generateFanoutTree(
    Resizer& resizer_,
    const Target& target,
    sta::Pin* drvr_pin,
    sta::Net* drvr_net,
    const std::vector<FanoutSlack>& ranked)
{
  std::vector<std::unique_ptr<MoveCandidate>> candidates;
  const float drvr_res = resizer_.driveResistance(drvr_pin);
  const std::vector<BufferModel> models = buildBufferModels(resizer_);
  if (models.empty() || drvr_res <= 0.0f) {
    return candidates;
  }

  // `ranked` is most-slack-first; the tree wants the most critical first.
  std::vector<TreeSink> sinks;
  sinks.reserve(ranked.size());
  float total_cap = 0.0f;
  for (auto it = ranked.rbegin(); it != ranked.rend(); ++it) {
    sta::Pin* pin = it->first->pin();
    const sta::LibertyPort* port = resizer_.network()->libertyPort(pin);
    const bool is_port = resizer_.network()->isTopLevelPort(pin);
    const float cap = port != nullptr ? port->capacitance() : 0.0f;
    sinks.push_back({pin,
                     cap,
                     static_cast<float>(it->second),
                     resizer_.dbNetwork()->location(pin),
                     is_port || port == nullptr});
    if (!is_port) {
      total_cap += cap;
    }
  }
  if (total_cap <= 0.0f) {
    return candidates;
  }

  TreePlan best;
  for (const float fraction : kDirectCapFractions) {
    for (int groups = 1; groups <= kTreeMaxGroups; ++groups) {
      TreePlan plan = evaluateVariant(
          sinks, models, drvr_res, total_cap, fraction, groups);
      if (plan.group_buf.empty()) {
        continue;
      }
      if (plan.score > best.score) {
        best = std::move(plan);
      }
    }
  }
  if (best.group_buf.empty() || best.score < kTreeMinGain) {
    ++fanoutTreeStats().stock_fallback;
    return candidates;
  }

  std::vector<FanoutTreeGroup> groups;
  for (size_t g = 0; g < best.group_buf.size(); ++g) {
    FanoutTreeGroup group;
    group.loads = std::make_unique<sta::PinSet>(resizer_.network());
    int64_t sx = 0;
    int64_t sy = 0;
    int count = 0;
    for (int i = best.group_begin[g]; i < best.group_begin[g + 1]; ++i) {
      if (sinks[i].is_port) {
        continue;
      }
      group.loads->insert(sinks[i].pin);
      sx += sinks[i].loc.x();
      sy += sinks[i].loc.y();
      ++count;
    }
    if (count == 0) {
      continue;
    }
    group.loc = odb::Point(static_cast<int>(sx / count),
                           static_cast<int>(sy / count));
    group.buffer_cell = models[best.group_buf[g]].cell;
    groups.push_back(std::move(group));
  }
  if (groups.empty()) {
    return candidates;
  }
  candidates.push_back(std::make_unique<SplitLoadCandidate>(
      resizer_, target, drvr_net, std::move(groups)));
  return candidates;
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

  std::vector<FanoutSlack> fanout_slacks
      = collectRankedFanoutSlacks(resizer_, target, drvr_vertex);
  if (fanout_slacks.empty()) {
    return candidates;
  }

  odb::dbNet* db_drvr_net = nullptr;
  odb::dbModNet* db_mod_drvr_net = nullptr;
  resizer_.dbNetwork()->net(drvr_pin, db_drvr_net, db_mod_drvr_net);
  sta::Net* drvr_net = resizer_.dbNetwork()->dbToSta(db_drvr_net);

  // High-fanout shared drivers: LT-tree instead of the stock half split.
  if (drvr_net != nullptr
      && static_cast<int>(fanout_slacks.size()) >= kTreeMinFanout) {
    candidates = generateFanoutTree(
        resizer_, target, drvr_pin, drvr_net, fanout_slacks);
    if (!candidates.empty()) {
      return candidates;
    }
  }

  std::unique_ptr<sta::PinSet> load_pins
      = chooseSplitLoads(resizer_, fanout_slacks);
  if (load_pins->empty()) {
    return candidates;
  }

  sta::LibertyCell* buffer_cell = resizer_.lowestDriveBufferCell();
  if (buffer_cell == nullptr || drvr_net == nullptr) {
    return candidates;
  }

  const odb::Point drvr_loc = resizer_.dbNetwork()->location(drvr_pin);
  candidates.push_back(std::make_unique<SplitLoadCandidate>(
      resizer_, target, drvr_net, buffer_cell, drvr_loc, std::move(load_pins)));
  return candidates;
}

}  // namespace rsz
