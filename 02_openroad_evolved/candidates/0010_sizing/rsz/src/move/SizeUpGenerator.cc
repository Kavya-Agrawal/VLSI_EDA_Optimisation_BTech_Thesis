// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SizeUpGenerator.hh"

#include <algorithm>
#include <array>
#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "SizeUpCandidate.hh"
#include "db_sta/dbNetwork.hh"
#include "db_sta/dbSta.hh"
#include "odb/db.h"
#include "rsz/Resizer.hh"
#include "sta/Graph.hh"
#include "sta/GraphDelayCalc.hh"
#include "sta/Liberty.hh"
#include "sta/LibertyClass.hh"
#include "sta/MinMax.hh"
#include "sta/Network.hh"
#include "sta/NetworkClass.hh"
#include "sta/Path.hh"
#include "sta/Scene.hh"
#include "sta/TimingArc.hh"
#include "sta/Transition.hh"

namespace rsz {

SizeUpGenerator::SizeUpGenerator(const GeneratorContext& context)
    : MoveGenerator(context)
{
}

SizeUpGenerator::~SizeUpGenerator()
{
  resizer_.logger()->report("RSZ_EVOLVE sizing_choice_differs fired={}",
                            choice_differs_count_);
  resizer_.logger()->report("RSZ_EVOLVE sizing_neighbor_weighted fired={}",
                            neighbor_weighted_count_);
  resizer_.logger()->report("RSZ_EVOLVE sizing_selections fired={}",
                            selections_count_);
}

std::vector<std::unique_ptr<MoveCandidate>> SizeUpGenerator::generate(
    const Target& target)
{
  std::vector<std::unique_ptr<MoveCandidate>> candidates;
  // Build one conventional size-up candidate from the active timing stage.
  sta::Pin* drvr_pin = nullptr;
  sta::Instance* inst = nullptr;
  sta::LibertyPort* drvr_port = nullptr;
  if (!resolveDriverContext(target, drvr_pin, inst, drvr_port)) {
    return candidates;
  }

  const sta::Scene* scene = nullptr;
  const sta::MinMax* min_max = nullptr;
  float load_cap = 0.0f;
  float prev_drive = 0.0f;
  sta::LibertyPort* in_port = nullptr;
  const sta::RiseFall* in_rf = nullptr;
  const sta::RiseFall* drvr_rf = nullptr;
  if (!loadStageContext(target,
                        drvr_pin,
                        scene,
                        min_max,
                        load_cap,
                        in_port,
                        in_rf,
                        drvr_rf,
                        prev_drive)) {
    return candidates;
  }

  sta::LibertyCell* replacement = selectReplacement(
      in_port,
      in_rf,
      drvr_port,
      drvr_rf,
      load_cap,
      prev_drive,
      scene,
      min_max,
      drvr_pin);
  if (replacement == nullptr
      || !resizer_.replacementPreservesMaxCap(
          inst, replacement, scene != nullptr ? scene->mode() : nullptr)) {
    return candidates;
  }

  candidates.push_back(std::make_unique<SizeUpCandidate>(
      resizer_, target, drvr_pin, inst, replacement));
  return candidates;
}

bool SizeUpGenerator::resolveDriverContext(const Target& target,
                                           sta::Pin*& drvr_pin,
                                           sta::Instance*& inst,
                                           sta::LibertyPort*& drvr_port) const
{
  drvr_pin = target.driver_pin;
  if (drvr_pin == nullptr) {
    drvr_pin = target.endpoint_path->pin(resizer_.staState());
  }
  if (drvr_pin == nullptr) {
    return false;
  }

  inst = resizer_.network()->instance(drvr_pin);
  if (inst == nullptr || resizer_.dontTouch(inst) || resizer_.isFixed(inst)
      || !resizer_.isLogicStdCell(inst)) {
    return false;
  }

  drvr_port = resizer_.network()->libertyPort(drvr_pin);
  return drvr_port != nullptr;
}

bool SizeUpGenerator::loadStageContext(const Target& target,
                                       sta::Pin* drvr_pin,
                                       const sta::Scene*& scene,
                                       const sta::MinMax*& min_max,
                                       float& load_cap,
                                       sta::LibertyPort*& in_port,
                                       const sta::RiseFall*& in_rf,
                                       const sta::RiseFall*& drvr_rf,
                                       float& prev_drive) const
{
  // Use the current path stage and the upstream driver to estimate delay gain.
  scene = target.activeScene(resizer_);
  min_max = target.minMax(resizer_);
  load_cap
      = resizer_.sta()->graphDelayCalc()->loadCap(drvr_pin, scene, min_max);

  const sta::Path* prev_drvr_path = target.prevDriverPath(resizer_);
  const sta::Path* drvr_path = target.driverPath(resizer_);
  const sta::TimingArc* in_arc = drvr_path != nullptr
                                     ? drvr_path->prevArc(resizer_.staState())
                                     : nullptr;
  in_port = in_arc != nullptr ? in_arc->from() : nullptr;
  if (in_port == nullptr) {
    return false;
  }
  in_rf = in_arc->fromEdge()->asRiseFall();
  drvr_rf = in_arc->toEdge()->asRiseFall();

  prev_drive = 0.0f;
  if (prev_drvr_path != nullptr) {
    sta::Pin* prev_drvr_pin = prev_drvr_path->pin(resizer_.staState());
    sta::LibertyPort* prev_drvr_port
        = prev_drvr_pin != nullptr
              ? resizer_.network()->libertyPort(prev_drvr_pin)
              : nullptr;
    if (prev_drvr_port != nullptr) {
      const int lib_ap = scene->libertyIndex(min_max);
      const sta::LibertyPort* scene_prev_drvr_port
          = static_cast<const sta::LibertyPort*>(prev_drvr_port)
                ->scenePort(lib_ap);
      if (scene_prev_drvr_port != nullptr) {
        prev_drive = scene_prev_drvr_port->driveResistance(in_rf, min_max);
      } else {
        prev_drive = prev_drvr_port->driveResistance(in_rf, min_max);
      }
    }
  }
  return true;
}

sta::LibertyCell* SizeUpGenerator::selectReplacement(
    sta::LibertyPort* in_port,
    const sta::RiseFall* in_rf,
    sta::LibertyPort* drvr_port,
    const sta::RiseFall* drvr_rf,
    const float load_cap,
    const float prev_drive,
    const sta::Scene* scene,
    const sta::MinMax* min_max,
    const sta::Pin* drvr_pin) const
{
  return upsizeCell(in_port,
                    in_rf,
                    drvr_port,
                    drvr_rf,
                    load_cap,
                    prev_drive,
                    scene,
                    min_max,
                    drvr_pin);
}

enum class CostType
{
  kLeakage,
  kLefArea,
  kLibArea
};

sta::LibertyCell* SizeUpGenerator::upsizeCell(sta::LibertyPort* in_port,
                                              const sta::RiseFall* in_rf,
                                              sta::LibertyPort* drvr_port,
                                              const sta::RiseFall* drvr_rf,
                                              const float load_cap,
                                              const float prev_drive,
                                              const sta::Scene* scene,
                                              const sta::MinMax* min_max,
                                              const sta::Pin* drvr_pin) const
{
  if (scene == nullptr || min_max == nullptr || in_port == nullptr
      || drvr_port == nullptr) {
    return nullptr;
  }

  const int lib_ap = scene->libertyIndex(min_max);
  sta::LibertyCell* cell = drvr_port->libertyCell();
  sta::LibertyCellSeq swappable_cells = resizer_.getSwappableCells(cell);
  debugPrint(resizer_.logger(),
             utl::RSZ,
             "size_up_move",
             3,
             "upsizeCell {}: {} swappable cells",
             cell->name(),
             swappable_cells.size());
  if (swappable_cells.empty()) {
    return nullptr;
  }

  // Cost of a nominal cell under one metric; nullopt if unavailable.
  auto cost_of = [this](sta::LibertyCell* c,
                        const CostType type) -> std::optional<float> {
    switch (type) {
      case CostType::kLeakage: {
        const std::optional<float> leak = resizer_.cellLeakage(c);
        return (leak && *leak > 0.0f) ? leak : std::nullopt;
      }
      case CostType::kLefArea: {
        auto* db_network = resizer_.dbNetwork();
        if (db_network != nullptr) {
          const odb::dbMaster* master = db_network->staToDb(c);
          if (master != nullptr && master->getArea() > 0) {
            return static_cast<float>(master->getArea());
          }
        }
        return std::nullopt;
      }
      case CostType::kLibArea:
        return c->area() > 0.0f ? std::optional<float>(c->area())
                                : std::nullopt;
    }
    return std::nullopt;
  };

  // Original cell costs under each metric, precomputed once: `cell` is constant
  // across the candidate loop, so this avoids repeating the staToDb/cellLeakage
  // lookups for the old cell on every swappable candidate.
  const std::array<std::optional<float>, 3> cell_costs
      = {cost_of(cell, CostType::kLeakage),
         cost_of(cell, CostType::kLefArea),
         cost_of(cell, CostType::kLibArea)};

  // new/old cost on the first metric BOTH cells support (never mixes units).
  auto cost_ratio = [&](sta::LibertyCell* new_cell) -> std::optional<float> {
    for (const CostType type :
         {CostType::kLeakage, CostType::kLefArea, CostType::kLibArea}) {
      const std::optional<float>& old_cost = cell_costs[static_cast<int>(type)];
      const std::optional<float> new_cost = cost_of(new_cell, type);
      if (old_cost && new_cost) {
        return *new_cost / *old_cost;
      }
    }
    return std::nullopt;
  };

  // Evaluate weaker equivalent cells first so iteration favors the smallest
  // adequate size-up step.
  const std::string& in_port_name = in_port->name();
  const std::string& drvr_port_name = drvr_port->name();
  const sta::LibertyPort* scene_drvr_port
      = static_cast<const sta::LibertyPort*>(drvr_port)->scenePort(lib_ap);
  const sta::LibertyPort* scene_input_port
      = static_cast<const sta::LibertyPort*>(in_port)->scenePort(lib_ap);
  if (scene_drvr_port == nullptr || scene_input_port == nullptr) {
    return nullptr;
  }

  const float drive_r_rise
      = scene_drvr_port->driveResistance(sta::RiseFall::rise(), min_max);
  const float drive_r_fall
      = scene_drvr_port->driveResistance(sta::RiseFall::fall(), min_max);
  const float in_cap = in_rf != nullptr
                           ? scene_input_port->capacitance(in_rf, min_max)
                           : scene_input_port->capacitance();
  const float delay
      = (drvr_rf != nullptr
             ? resizer_.gateDelay(drvr_port, drvr_rf, load_cap, scene, min_max)
             : resizer_.gateDelay(drvr_port, load_cap, scene, min_max))
        + prev_drive * in_cap;

  // Violation weights (lambda = max(0,-slack)/|WNS|, clamped to [0,1]) of the
  // upstream driver and of the side loads of the input net. Raising the input
  // pin cap slows all of them, so the upstream penalty is charged by
  // 1 + sum(lambda). With no violating neighbours this is exactly stock.
  float up_weight = 1.0f;
  {
    sta::dbSta* sta_obj = resizer_.sta();
    sta::Network* network = resizer_.network();
    const sta::MinMax* max_mm = resizer_.maxAnalysisMode();
    const float wns = sta::delayAsFloat(sta_obj->worstSlack(max_mm));
    const float wns_abs = std::max(std::abs(wns), 1e-15f);
    auto lambda_of = [&](sta::Vertex* v) -> float {
      if (v == nullptr || wns >= 0.0f) {
        return 0.0f;
      }
      const float slack = sta::delayAsFloat(sta_obj->slack(v, max_mm));
      if (slack >= 0.0f || slack < -1e30f) {
        return 0.0f;
      }
      return std::min(1.0f, -slack / wns_abs);
    };
    const sta::Instance* drvr_inst
        = drvr_pin != nullptr ? network->instance(drvr_pin) : nullptr;
    const sta::Pin* in_pin
        = drvr_inst != nullptr ? network->findPin(drvr_inst, in_port) : nullptr;
    const sta::Net* in_net = in_pin != nullptr ? network->net(in_pin) : nullptr;
    if (in_net != nullptr) {
      float sum = 0.0f;
      std::unique_ptr<sta::NetPinIterator> it(network->pinIterator(in_net));
      while (it->hasNext()) {
        const sta::Pin* p = it->next();
        if (p == in_pin) {
          continue;
        }
        if (network->isDriver(p)) {
          sum += lambda_of(resizer_.graph()->pinDrvrVertex(p));
        } else if (network->isLoad(p)) {
          sum += lambda_of(resizer_.graph()->pinLoadVertex(p));
        }
      }
      up_weight += std::min(sum, 4.0f);
    }
  }
  const float gate_delay_old
      = drvr_rf != nullptr
            ? resizer_.gateDelay(drvr_port, drvr_rf, load_cap, scene, min_max)
            : resizer_.gateDelay(drvr_port, load_cap, scene, min_max);

  // Among cells that do not weaken drive resistance on either edge and improve
  // stage delay (corner-robust eligibility that protects downstream max-slew/
  // max-cap), pick the most cost-effective by delay-gain per unit power rather
  // than the first adequate cell, to avoid over-sizing.
  sta::LibertyCell* stock_cell = nullptr;
  float stock_score = 0.0f;
  sta::LibertyCell* weighted_cell = nullptr;
  float weighted_score = 0.0f;
  for (sta::LibertyCell* swappable : swappable_cells) {
    if (swappable == cell) {
      continue;
    }
    sta::LibertyCell* swappable_corner = swappable->sceneCell(lib_ap);
    if (swappable_corner == nullptr) {
      continue;
    }
    sta::LibertyPort* swappable_drvr
        = swappable_corner->findLibertyPort(drvr_port_name);
    sta::LibertyPort* swappable_input
        = swappable_corner->findLibertyPort(in_port_name);
    if (swappable_drvr == nullptr || swappable_input == nullptr) {
      continue;
    }
    const float swappable_drive_r_rise
        = swappable_drvr->driveResistance(sta::RiseFall::rise(), min_max);
    const float swappable_drive_r_fall
        = swappable_drvr->driveResistance(sta::RiseFall::fall(), min_max);
    const float swappable_in_cap
        = in_rf != nullptr ? swappable_input->capacitance(in_rf, min_max)
                           : swappable_input->capacitance();
    const float swappable_delay
        = (drvr_rf != nullptr
               ? resizer_.gateDelay(
                     swappable_drvr, drvr_rf, load_cap, scene, min_max)
               : resizer_.gateDelay(swappable_drvr, load_cap, scene, min_max))
          + prev_drive * swappable_in_cap;
    // Eligibility (upstream): stronger-or-equal drive on both edges and faster.
    if (swappable_drive_r_rise > drive_r_rise
        || swappable_drive_r_fall > drive_r_fall || swappable_delay >= delay) {
      continue;
    }
    // Selection: best delay-gain per unit power among eligible candidates.
    const std::optional<float> ratio = cost_ratio(swappable);
    if (!ratio) {
      continue;
    }
    const float denom = std::max(1.0f, *ratio);
    const float score = (delay - swappable_delay) / denom;
    if (score > stock_score) {
      stock_cell = swappable;
      stock_score = score;
    }
    // Criticality-weighted score: own-stage gain minus the upstream/side-load
    // delay increase, charged by violation weight.
    const float gate_delay_new
        = swappable_delay - prev_drive * swappable_in_cap;
    const float up_pen = prev_drive * (swappable_in_cap - in_cap);
    const float wscore
        = ((gate_delay_old - gate_delay_new) - up_weight * up_pen) / denom;
    if (weighted_cell == nullptr || wscore > weighted_score) {
      weighted_cell = swappable;
      weighted_score = wscore;
    }
  }

  if (stock_cell != nullptr) {
    ++selections_count_;
    if (up_weight > 1.0f) {
      ++neighbor_weighted_count_;
    }
    if (weighted_cell != stock_cell) {
      ++choice_differs_count_;
    }
  }
  return weighted_cell;
}

}  // namespace rsz
