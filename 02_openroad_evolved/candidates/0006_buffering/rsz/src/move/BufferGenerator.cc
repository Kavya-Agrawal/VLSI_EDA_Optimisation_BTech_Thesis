// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "BufferGenerator.hh"

#include <cmath>
#include <memory>
#include <vector>

#include "BufferCandidate.hh"
#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "db_sta/dbSta.hh"
#include "rsz/Resizer.hh"
#include "sta/Delay.hh"
#include "sta/Graph.hh"
#include "sta/MinMax.hh"
#include "sta/Mode.hh"

namespace rsz {

namespace {

constexpr int kRebufferMaxFanout = 20;

}  // namespace

BufferGenerator::BufferGenerator(const GeneratorContext& context)
    : MoveGenerator(context)
{
}

bool BufferGenerator::isApplicable(const Target& target) const
{
  if (!MoveGenerator::isApplicable(target) || target.fanout < 1
      || !resizer_.okToBufferNet(target.driver_pin)) {
    return false;
  }
  if (target.fanout < kRebufferMaxFanout) {
    return true;
  }

  // Larger trees are worth searching when multiple immediate data loads
  // share setup criticality on the selected transition.
  const sta::Mode* mode = target.mode(resizer_);
  sta::dbSta* sta = resizer_.sta();
  if (target.minMax(resizer_) != sta::MinMax::max()
      || target.driver_rf == nullptr || mode == nullptr
      || sta->isClock(target.driver_pin, mode)
      || sta->isClockSrc(target.driver_pin, mode->sdc())) {
    return false;
  }

  sta::Graph* graph = resizer_.graph();
  sta::Vertex* driver_vertex = graph->pinDrvrVertex(target.driver_pin);
  if (driver_vertex == nullptr) {
    return false;
  }

  const sta::Pin* first_critical_load = nullptr;
  sta::VertexOutEdgeIterator edge_iter(driver_vertex, graph);
  while (edge_iter.hasNext()) {
    sta::Edge* edge = edge_iter.next();
    if (!edge->isWire()) {
      continue;
    }
    sta::Vertex* load_vertex = edge->to(graph);
    const float slack = sta::delayAsFloat(
        sta->slack(load_vertex, target.driver_rf, resizer_.maxAnalysisMode()));
    // Reject unconstrained sentinels as well as IEEE infinities and NaNs.
    if (std::isfinite(slack) && slack > -sta::INF && slack < 0.0f) {
      const sta::Pin* load_pin = load_vertex->pin();
      if (first_critical_load != nullptr && first_critical_load != load_pin) {
        return true;
      }
      first_critical_load = load_pin;
    }
  }
  return false;
}

std::vector<std::unique_ptr<MoveCandidate>> BufferGenerator::generate(
    const Target& target)
{
  std::vector<std::unique_ptr<MoveCandidate>> candidates;
  candidates.push_back(
      std::make_unique<BufferCandidate>(resizer_, target, target.driver_pin));
  return candidates;
}

}  // namespace rsz
