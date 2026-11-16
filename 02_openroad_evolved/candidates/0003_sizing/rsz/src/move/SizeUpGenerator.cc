// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SizeUpGenerator.hh"

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "SizeUpCandidate.hh"
#include "db_sta/dbSta.hh"
#include "rsz/Resizer.hh"
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

std::vector<std::unique_ptr<MoveCandidate>> SizeUpGenerator::generate(
    const Target& target)
{
  std::vector<std::unique_ptr<MoveCandidate>> candidates;
  // Rank viable size-up candidates from the active timing stage.
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

  for (sta::LibertyCell* replacement : selectReplacements(in_port,
                                                          in_rf,
                                                          drvr_port,
                                                          drvr_rf,
                                                          load_cap,
                                                          prev_drive,
                                                          scene,
                                                          min_max)) {
    if (!resizer_.replacementPreservesMaxCap(
            inst, replacement, scene != nullptr ? scene->mode() : nullptr)) {
      continue;
    }
    candidates.push_back(std::make_unique<SizeUpCandidate>(
        resizer_, target, drvr_pin, inst, replacement));
  }
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
  load_cap =
      resizer_.sta()->graphDelayCalc()->loadCap(drvr_pin, scene, min_max);

  const sta::Path* prev_drvr_path = target.prevDriverPath(resizer_);
  const sta::Path* drvr_path = target.driverPath(resizer_);
  const sta::TimingArc* in_arc =
      drvr_path != nullptr ? drvr_path->prevArc(resizer_.staState()) : nullptr;
  in_port = in_arc != nullptr ? in_arc->from() : nullptr;
  if (in_port == nullptr) {
    return false;
  }
  in_rf = in_arc->fromEdge()->asRiseFall();
  drvr_rf = in_arc->toEdge()->asRiseFall();

  prev_drive = 0.0f;
  if (prev_drvr_path != nullptr) {
    sta::Pin* prev_drvr_pin = prev_drvr_path->pin(resizer_.staState());
    sta::LibertyPort* prev_drvr_port =
        prev_drvr_pin != nullptr
            ? resizer_.network()->libertyPort(prev_drvr_pin)
            : nullptr;
    if (prev_drvr_port != nullptr) {
      const int lib_ap = scene->libertyIndex(min_max);
      const sta::LibertyPort* scene_prev_drvr_port =
          static_cast<const sta::LibertyPort*>(prev_drvr_port)
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

std::vector<sta::LibertyCell*> SizeUpGenerator::selectReplacements(
    sta::LibertyPort* in_port,
    const sta::RiseFall* in_rf,
    sta::LibertyPort* drvr_port,
    const sta::RiseFall* drvr_rf,
    const float load_cap,
    const float prev_drive,
    const sta::Scene* scene,
    const sta::MinMax* min_max) const
{
  return upsizeCells(
      in_port, in_rf, drvr_port, drvr_rf, load_cap, prev_drive, scene, min_max);
}

std::vector<sta::LibertyCell*> SizeUpGenerator::upsizeCells(
    sta::LibertyPort* in_port,
    const sta::RiseFall* in_rf,
    sta::LibertyPort* drvr_port,
    const sta::RiseFall* drvr_rf,
    const float load_cap,
    const float prev_drive,
    const sta::Scene* scene,
    const sta::MinMax* min_max) const
{
  if (scene == nullptr || min_max == nullptr || in_port == nullptr
      || drvr_port == nullptr) {
    return {};
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
    return {};
  }

  const std::string& in_port_name = in_port->name();
  const std::string& drvr_port_name = drvr_port->name();
  const sta::LibertyPort* scene_drvr_port =
      static_cast<const sta::LibertyPort*>(drvr_port)->scenePort(lib_ap);
  const sta::LibertyPort* scene_input_port =
      static_cast<const sta::LibertyPort*>(in_port)->scenePort(lib_ap);
  if (scene_drvr_port == nullptr || scene_input_port == nullptr) {
    return {};
  }

  const float drive_r_rise =
      scene_drvr_port->driveResistance(sta::RiseFall::rise(), min_max);
  const float drive_r_fall =
      scene_drvr_port->driveResistance(sta::RiseFall::fall(), min_max);
  const float in_cap = in_rf != nullptr
                           ? scene_input_port->capacitance(in_rf, min_max)
                           : scene_input_port->capacitance();
  const float delay =
      (drvr_rf != nullptr
           ? resizer_.gateDelay(drvr_port, drvr_rf, load_cap, scene, min_max)
           : resizer_.gateDelay(drvr_port, load_cap, scene, min_max))
      + prev_drive * in_cap;

  // Rank by stage delay gain, including the upstream delay cost of the
  // replacement's input capacitance.  Area and leakage remain constrained by
  // getSwappableCells(), but do not dilute the timing benefit in this ranking.
  std::vector<std::pair<sta::LibertyCell*, float>> ranked_cells;
  for (sta::LibertyCell* swappable : swappable_cells) {
    if (swappable == cell) {
      continue;
    }
    sta::LibertyCell* swappable_corner = swappable->sceneCell(lib_ap);
    if (swappable_corner == nullptr) {
      continue;
    }
    sta::LibertyPort* swappable_drvr =
        swappable_corner->findLibertyPort(drvr_port_name);
    sta::LibertyPort* swappable_input =
        swappable_corner->findLibertyPort(in_port_name);
    if (swappable_drvr == nullptr || swappable_input == nullptr) {
      continue;
    }
    const float swappable_drive_r_rise =
        swappable_drvr->driveResistance(sta::RiseFall::rise(), min_max);
    const float swappable_drive_r_fall =
        swappable_drvr->driveResistance(sta::RiseFall::fall(), min_max);
    const float swappable_in_cap =
        in_rf != nullptr ? swappable_input->capacitance(in_rf, min_max)
                         : swappable_input->capacitance();
    const float swappable_delay =
        (drvr_rf != nullptr
             ? resizer_.gateDelay(
                   swappable_drvr, drvr_rf, load_cap, scene, min_max)
             : resizer_.gateDelay(swappable_drvr, load_cap, scene, min_max))
        + prev_drive * swappable_in_cap;
    // Eligibility (upstream): stronger-or-equal drive on both edges and faster.
    if (swappable_drive_r_rise > drive_r_rise
        || swappable_drive_r_fall > drive_r_fall || swappable_delay >= delay) {
      continue;
    }
    const float gain = delay - swappable_delay;
    if (std::isfinite(gain) && gain > 0.0f) {
      ranked_cells.emplace_back(swappable, gain);
    }
  }

  std::stable_sort(ranked_cells.begin(),
                   ranked_cells.end(),
                   [](const auto& lhs, const auto& rhs) {
                     if (lhs.second != rhs.second) {
                       return lhs.second > rhs.second;
                     }
                     if (lhs.first->name() != rhs.first->name()) {
                       return lhs.first->name() < rhs.first->name();
                     }
                     return lhs.first->library()->name()
                            < rhs.first->library()->name();
                   });

  std::vector<sta::LibertyCell*> replacements;
  for (const auto& ranked : ranked_cells) {
    replacements.push_back(ranked.first);
  }
  return replacements;
}

}  // namespace rsz
