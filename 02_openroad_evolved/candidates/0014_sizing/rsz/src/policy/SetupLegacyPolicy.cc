// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SetupLegacyPolicy.hh"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <tuple>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

#include "MoveCommitter.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "RepairSetupProfiler.hh"
#include "RepairTargetCollector.hh"
#include "est/EstimateParasitics.h"
#include "policy/OptimizationPolicy.hh"
#include "rsz/Resizer.hh"
#include "sta/Delay.hh"
#include "sta/Fuzzy.hh"
#include "sta/Graph.hh"
#include "sta/GraphClass.hh"
#include "sta/GraphDelayCalc.hh"
#include "sta/Liberty.hh"
#include "sta/MinMax.hh"
#include "sta/Scene.hh"
#include "sta/TimingArc.hh"
#include "sta/Transition.hh"
#include "sta/Network.hh"
#include "sta/NetworkClass.hh"
#include "sta/Path.hh"
#include "sta/PathExpanded.hh"
#include "utl/Logger.h"
#include "utl/timer.h"

namespace rsz {

using std::pair;
using utl::RSZ;

namespace {
static constexpr int kDelayDigits = 3;

}  // namespace

void SetupLegacyPolicy::iterate()
{
  committer_.tracker().capturePrePhaseSlack();
  buildMainMoveSequence(/*log_sequence=*/false);

  MainRepairState main_state;
  main_state.opto_iteration = setup_context_.iteration;
  main_state.initial_tns = setup_context_.initial_tns;
  main_state.prev_tns = setup_context_.initial_tns;
  main_state.phase_marker = phaseMarkerForIndex(setup_context_.phase_index);

  ViolatingEnds violating_ends;
  if (initializeMainRepair(main_state, violating_ends)) {
    runMainRepairLoop(violating_ends, main_state);
  }

  if (std::strcmp(phaseName(), "LEGACY") == 0) {
    runTnsRecovery();
  }

  committer_.printTrackerPhaseSummary(
      phaseSummaryTitle(), phaseEndpointProfilerTitle(), true);

  // Propagate accumulator deltas back to the sequencer.
  setup_context_.iteration = main_state.opto_iteration;
  setup_context_.violation_count = main_state.num_viols;
  setup_context_.initial_tns = main_state.initial_tns;
  setup_context_.previous_tns = main_state.prev_tns;
  markRunComplete(true);
}

bool SetupLegacyPolicy::initializeMainRepair(MainRepairState& main_state,
                                             ViolatingEnds& violating_ends)
{
  const float setup_slack_margin = config_.setup_slack_margin;
  violating_ends = collectViolatingEndpoints(setup_slack_margin);

  // prepareForPhasePipeline already rejected the zero-violation case, but the
  // collector can re-filter here if slack margin semantics differ.
  if (violating_ends.empty()) {
    RepairSetupProfiler::stop("no_violating_endpoints");
    debugPrint(logger_,
               RSZ,
               "repair_setup",
               1,
               "{}{} Phase: No violating endpoints, exiting",
               phaseName(),
               main_state.phase_marker);
    return false;
  }

  debugPrint(logger_,
             RSZ,
             "repair_setup",
             1,
             "{}{} Phase: {} violating endpoints found",
             phaseName(),
             main_state.phase_marker,
             violating_ends.size());

  main_state.max_end_count = std::max(
      static_cast<int>(violating_ends.size() * config_.repair_tns_end_percent),
      1);
  main_state.initial_tns = totalNegativeSlack();
  main_state.prev_tns = main_state.initial_tns;
  main_state.num_viols = violating_ends.size();
  main_state.fix_rate_threshold = inc_fix_rate_threshold_;

  printProgress(main_state.opto_iteration, false, main_state.phase_marker);

  setup_context_.min_viol = -violating_ends.back().second;
  setup_context_.max_viol = -violating_ends.front().second;
  return true;
}

bool SetupLegacyPolicy::beginEndpointRepair(
    const pair<sta::Vertex*, sta::Slack>& end_original_slack,
    MainRepairState& main_state,
    EndpointRepairState& endpoint_state)
{
  if (!beginJournaledEndpointSearch(end_original_slack,
                                    main_state.max_end_count,
                                    main_state.end_index,
                                    endpoint_state)) {
    return false;
  }

  debugPrint(logger_,
             RSZ,
             "repair_setup",
             1,
             "{}{} Phase: Doing endpoint {} ({}/{}) WNS = {}, "
             "endpoint slack = {}, TNS = {}",
             phaseName(),
             main_state.phase_marker,
             endpoint_state.end->name(network_),
             main_state.end_index,
             main_state.max_end_count,
             delayAsString(endpoint_state.worst_slack, kDelayDigits, sta_),
             delayAsString(endpoint_state.end_slack, kDelayDigits, sta_),
             delayAsString(main_state.prev_tns, 1, sta_));

  endpoint_state.prev_end_slack = endpoint_state.end_slack;
  endpoint_state.prev_worst_slack = endpoint_state.worst_slack;
  return true;
}

void SetupLegacyPolicy::repairEndpoint(EndpointRepairState& endpoint_state,
                                       MainRepairState& main_state)
{
  const float setup_slack_margin = config_.setup_slack_margin;
  while (endpoint_state.pass <= config_.max_passes) {
    const ProfileIteration iteration("legacy_pass");
    ++main_state.opto_iteration;
    if (config_.verbose || main_state.opto_iteration == 1) {
      printProgress(main_state.opto_iteration, false, main_state.phase_marker);
    }

    if (terminateProgress(main_state.opto_iteration,
                          main_state.initial_tns,
                          main_state.prev_tns,
                          main_state.fix_rate_threshold,
                          main_state.end_index,
                          main_state.max_end_count,
                          phaseName(),
                          main_state.phase_marker)) {
      recordTermination(main_state.prev_termination,
                        main_state.two_cons_terminations);
      debugPrint(
          logger_,
          RSZ,
          "repair_setup",
          2,
          "{}{} Phase: Restoring best slack; endpoint slack = {}, "
          "WNS = {}",
          phaseName(),
          main_state.phase_marker,
          delayAsString(endpoint_state.prev_end_slack, kDelayDigits, sta_),
          delayAsString(endpoint_state.prev_worst_slack, kDelayDigits, sta_));
      restoreEndpointState(endpoint_state);
      break;
    }
    if (main_state.opto_iteration % opto_small_interval_ == 0) {
      main_state.prev_termination = false;
    }

    // Exit early once the endpoint is clean or the move sequence stalls.
    if (sta::fuzzyGreaterEqual(endpoint_state.end_slack, setup_slack_margin)) {
      RepairSetupProfiler::stop("endpoint_repaired");
      --main_state.num_viols;
      debugPrint(logger_,
                 RSZ,
                 "repair_setup",
                 1,
                 "{}{} Phase: Endpoint slack {} meets slack margin {}, "
                 "done",
                 phaseName(),
                 main_state.phase_marker,
                 delayAsString(endpoint_state.worst_slack, kDelayDigits, sta_),
                 delayAsString(setup_slack_margin, kDelayDigits, sta_));
      finishEndpointSearch(endpoint_state);
      break;
    }

    const bool log_change_summary = logger_->debugCheck(RSZ, "repair_setup", 3);
    float prev_tns_local = 0.0;
    if (log_change_summary) {
      prev_tns_local = totalNegativeSlack();
    }

    sta::Path* end_path = endpointWorstPath(endpoint_state.end);
    const bool changed = repairPath(
        end_path, endpoint_state.end_slack, endpoint_state.force_single_repair);
    if (!changed) {
      RepairSetupProfiler::stop("no_change");
      if (endpoint_state.pass != 1) {
        debugPrint(logger_,
                   RSZ,
                   "repair_setup",
                   2,
                   "{}{} Phase: No change after {} decreasing slack "
                   "passes.",
                   phaseName(),
                   main_state.phase_marker,
                   endpoint_state.decreasing_slack_passes);
        debugPrint(
            logger_,
            RSZ,
            "repair_setup",
            2,
            "{}{} Phase: Restoring best slack; endpoint slack = "
            "{}, WNS = {}",
            phaseName(),
            main_state.phase_marker,
            delayAsString(endpoint_state.prev_end_slack, kDelayDigits, sta_),
            delayAsString(endpoint_state.prev_worst_slack, kDelayDigits, sta_));
      }
      debugPrint(logger_,
                 RSZ,
                 "repair_setup",
                 1,
                 "{}{} Phase: No change possible for endpoint {} ",
                 phaseName(),
                 main_state.phase_marker,
                 endpoint_state.end->name(network_));
      finishEndpointSearch(endpoint_state);
      break;
    }

    resizer_.updateParasiticsAndTiming();
    refreshEndpointSlacks(endpoint_state);

    // Promote only the passes that improve the tracked objective.
    const bool better = pathImproved(endpoint_state.end_slack,
                                     endpoint_state.worst_slack,
                                     endpoint_state.prev_end_slack,
                                     endpoint_state.prev_worst_slack);

    float new_tns = 0.0f;

    // The profiler records the per-pass WNS/TNS trajectory even when the
    // debug summary does not need the TNS query.
    if (log_change_summary || RepairSetupProfiler::enabled()) {
      new_tns = totalNegativeSlack();
      RepairSetupProfiler::qor(
          "pass_after", endpoint_state.worst_slack, new_tns);
    }
    if (log_change_summary) {
      const ProfileScope profile("reporting");
      debugPrint(
          logger_,
          RSZ,
          "repair_setup",
          3,
          "{}{} Phase: {} after changes: WNS ({} -> {}) TNS "
          "({} -> {}) Endpoint slack ({} -> {})",
          phaseName(),
          main_state.phase_marker,
          better ? "Improved" : "Worsened",
          delayAsString(endpoint_state.prev_worst_slack, kDelayDigits, sta_),
          delayAsString(endpoint_state.worst_slack, kDelayDigits, sta_),
          delayAsString(prev_tns_local, 1, sta_),
          delayAsString(new_tns, 1, sta_),
          delayAsString(endpoint_state.prev_end_slack, kDelayDigits, sta_),
          delayAsString(endpoint_state.end_slack, kDelayDigits, sta_));
    }

    if (better) {
      if (sta::fuzzyGreaterEqual(endpoint_state.end_slack,
                                 setup_slack_margin)) {
        --main_state.num_viols;
      }
      endpoint_state.prev_end_slack = endpoint_state.end_slack;
      endpoint_state.prev_worst_slack = endpoint_state.worst_slack;
      endpoint_state.decreasing_slack_passes = 0;
      endpoint_state.force_single_repair = false;
      saveImprovedCheckpoint(endpoint_state);
    } else {
      RepairSetupProfiler::event("checkpoint_misses");
      endpoint_state.force_single_repair = true;
      ++endpoint_state.decreasing_slack_passes;
      if (endpoint_state.decreasing_slack_passes
          > decreasing_slack_max_passes_) {
        RepairSetupProfiler::stop("max_decreasing_slack_passes");
        debugPrint(logger_,
                   RSZ,
                   "repair_setup",
                   2,
                   "{}{} Phase: Endpoint {} stuck after {} "
                   "non-improving passes (limit {})",
                   phaseName(),
                   main_state.phase_marker,
                   network_->pathName(endpoint_state.end->pin()),
                   endpoint_state.decreasing_slack_passes,
                   decreasing_slack_max_passes_);
        debugPrint(
            logger_,
            RSZ,
            "repair_setup",
            2,
            "{}{} Phase: Restoring best slack; endpoint slack = "
            "{}, WNS = {}",
            phaseName(),
            main_state.phase_marker,
            delayAsString(endpoint_state.prev_end_slack, kDelayDigits, sta_),
            delayAsString(endpoint_state.prev_worst_slack, kDelayDigits, sta_));
        restoreEndpointState(endpoint_state);
        break;
      }
      debugPrint(logger_,
                 RSZ,
                 "repair_setup",
                 3,
                 "{}{} Phase: Allowing decreasing slack for {}/{} passes",
                 phaseName(),
                 main_state.phase_marker,
                 endpoint_state.decreasing_slack_passes,
                 decreasing_slack_max_passes_);
    }

    // Global guards stop searching and let post-loop cleanup finalize the
    // endpoint journal.
    if (resizer_.overMaxArea()) {
      RepairSetupProfiler::stop("max_area");
      debugPrint(logger_,
                 RSZ,
                 "repair_setup",
                 1,
                 "{}{} Phase: Over max area, exiting",
                 phaseName(),
                 main_state.phase_marker);
      break;
    }
    if (main_state.end_index == 1 && endpoint_state.worst_vertex != nullptr
        && endpoint_state.end != endpoint_state.worst_vertex) {
      endpoint_state.end = endpoint_state.worst_vertex;
      endpoint_state.end_slack = endpoint_state.worst_slack;
      target_collector_->useWorstEndpoint(endpoint_state.end);
      committer_.setCurrentEndpoint(endpoint_state.end->pin());
    }

    ++endpoint_state.pass;
    if (config_.max_iterations > 0
        && main_state.opto_iteration >= config_.max_iterations) {
      RepairSetupProfiler::stop("max_iterations");
      break;
    }

    if (endpoint_state.pass > config_.max_passes) {
      RepairSetupProfiler::stop("max_passes");
    }
  }

  if (endpoint_state.journal_open) {
    if (endpoint_state.decreasing_slack_passes > 0) {
      debugPrint(
          logger_,
          RSZ,
          "repair_setup",
          2,
          "{}{} Phase: Restoring best slack; endpoint slack = {}, "
          "WNS = {}",
          phaseName(),
          main_state.phase_marker,
          delayAsString(endpoint_state.prev_end_slack, kDelayDigits, sta_),
          delayAsString(endpoint_state.prev_worst_slack, kDelayDigits, sta_));
      restoreEndpointState(endpoint_state);
    } else {
      acceptEndpointState(endpoint_state);
    }
  }
}

void SetupLegacyPolicy::runMainRepairLoop(const ViolatingEnds& violating_ends,
                                          MainRepairState& main_state)
{
  const utl::DebugScopedTimer timer(
      logger_,
      RSZ,
      "repair_setup",
      10,
      fmt::format(
          "{}{} Phase Time: {{}}", phaseName(), main_state.phase_marker));
  for (const pair<sta::Vertex*, sta::Slack>& end_original_slack :
       violating_ends) {
    // Stop before starting a new endpoint after reaching the global limit.
    if (reachedIterationLimit(main_state.opto_iteration,
                              config_.max_iterations)) {
      RepairSetupProfiler::stop("max_iterations");
      break;
    }

    EndpointRepairState endpoint_state;
    if (!beginEndpointRepair(end_original_slack, main_state, endpoint_state)) {
      break;
    }

    repairEndpoint(endpoint_state, main_state);

    if (config_.verbose || main_state.opto_iteration == 1) {
      printProgress(main_state.opto_iteration, true, main_state.phase_marker);
    }
    if (main_state.two_cons_terminations) {
      RepairSetupProfiler::stop("consecutive_terminations");
      debugPrint(logger_,
                 RSZ,
                 "repair_setup",
                 1,
                 "{}{} Phase: Exiting due to no TNS progress for two "
                 "opto cycles",
                 phaseName(),
                 main_state.phase_marker);
      break;
    }
  }

  printProgress(main_state.opto_iteration, true, main_state.phase_marker);
  reportPhaseComplete(phaseName(), main_state.phase_marker);
}

void SetupLegacyPolicy::runTnsRecovery()
{
  constexpr int kTopPaths = 400;
  constexpr int kTopDrivers = 50;
  constexpr int kMaxRounds = 5;
  constexpr int kAttemptsPerDriver = 3;
  constexpr float kMinTnsGain = 0.5e-12f;

  int64_t trials = 0;
  int64_t kept = 0;
  int64_t rounds = 0;
  int64_t rejected_wns = 0;
  int64_t rejected_tns = 0;
  int64_t drivers_ranked = 0;

  const MoveType all_types[] = {MoveType::kSizeUp,
                                MoveType::kSizeUpMatch,
                                MoveType::kSizeDownFanout,
                                MoveType::kBuffer,
                                MoveType::kClone,
                                MoveType::kSwapPins,
                                MoveType::kVtSwap,
                                MoveType::kUnbuffer,
                                MoveType::kSplitLoad,
                                MoveType::kReroute};
  int stock_moves = 0;
  for (const MoveType type : all_types) {
    stock_moves += committedMoves(type);
  }
  const int move_cap = std::max(30, stock_moves / 10);

  // --- Joint path-window sizing (Viterbi DP over a window of path stages) ---
  constexpr int kWindowStages = 4;
  constexpr int kMaxCandsPerStage = 10;
  constexpr float kMinWindowGain = 1.0e-12f;
  constexpr float kSideWeight = 0.2f;
  constexpr float kAreaPenalty = 0.2e-12f;
  constexpr float kMaxAreaRatio = 8.0f;
  int64_t win_examined = 0;
  int64_t win_with_gain = 0;
  int64_t win_joint_differs = 0;
  int64_t win_stages_changed = 0;
  int64_t win_trials = 0;
  int64_t win_kept = 0;
  int64_t win_rejected_wns = 0;
  int64_t win_rejected_tns = 0;

  struct WindowStage
  {
    int path_index{0};
    const sta::Pin* pin{nullptr};
    sta::Instance* inst{nullptr};
    const sta::RiseFall* drvr_rf{nullptr};
    float load{0.0f};
    float side_load{0.0f};
    int side_fanout{0};
    std::vector<sta::LibertyCell*> cands;       // [0] = current master
    std::vector<const sta::LibertyPort*> outs;  // scene output ports
    std::vector<float> cin;                     // input cap per candidate
    std::vector<float> area;
  };

  // Plans a joint master assignment for a window around `drvr_pin` on the
  // current worst path to `end_pin`.  Returns true and fills `insts` /
  // `masters` with the instances to change when the DP finds a gain.
  auto planWindow = [&](const sta::Pin* drvr_pin,
                        const sta::Pin* end_pin,
                        const Target& target,
                        std::vector<sta::Instance*>& insts,
                        std::vector<sta::LibertyCell*>& masters) -> bool {
    const sta::Scene* scene = target.activeScene(resizer_);
    const sta::MinMax* min_max = target.minMax(resizer_);
    if (scene == nullptr || min_max == nullptr || end_pin == nullptr) {
      return false;
    }
    const int lib_ap = scene->libertyIndex(min_max);
    sta::Vertex* end_vertex = sta_->graph()->pinLoadVertex(end_pin);
    if (end_vertex == nullptr) {
      return false;
    }
    sta::Path* path = endpointWorstPath(end_vertex);
    if (path == nullptr) {
      return false;
    }
    sta::PathExpanded expanded(path, sta_);

    std::vector<WindowStage> all;
    std::vector<sta::LibertyPort*> in_ports;
    std::vector<const sta::RiseFall*> in_rfs;
    std::vector<sta::LibertyPort*> drvr_ports;
    int target_idx = -1;
    for (size_t k = expanded.startIndex(); k < expanded.size(); ++k) {
      const sta::Path* p = expanded.path(k);
      sta::Vertex* v = p->vertex(sta_);
      const sta::Pin* pin = p->pin(sta_);
      if (!v->isDriver(network_) || network_->isTopLevelPort(pin)) {
        continue;
      }
      const sta::TimingArc* arc = p->prevArc(sta_);
      sta::LibertyPort* dport = network_->libertyPort(pin);
      if (arc == nullptr || dport == nullptr || arc->from() == nullptr) {
        continue;
      }
      WindowStage st;
      st.path_index = static_cast<int>(k);
      st.pin = pin;
      st.inst = network_->instance(pin);
      st.drvr_rf = arc->toEdge()->asRiseFall();
      st.load = sta_->graphDelayCalc()->loadCap(pin, scene, min_max);
      st.side_fanout = std::max(0, fanout(v) - 1);
      if (pin == drvr_pin) {
        target_idx = static_cast<int>(all.size());
      }
      all.push_back(std::move(st));
      in_ports.push_back(arc->from());
      in_rfs.push_back(arc->fromEdge()->asRiseFall());
      drvr_ports.push_back(dport);
    }
    if (target_idx < 0) {
      return false;
    }
    const int total = static_cast<int>(all.size());
    auto contiguous = [&](int a) {  // stage a feeds stage a+1 directly
      return a >= 0 && a + 1 < total
             && all[a + 1].path_index == all[a].path_index + 2;
    };
    int lo = target_idx;
    int hi = target_idx;  // inclusive
    if (contiguous(lo - 1)) {
      --lo;
    }
    while (hi - lo + 1 < kWindowStages && contiguous(hi)) {
      ++hi;
    }
    while (hi - lo + 1 < kWindowStages && contiguous(lo - 1)) {
      --lo;
    }
    const int n = hi - lo + 1;
    if (n < 2) {
      return false;
    }

    // Candidate masters per stage.
    std::vector<WindowStage> w(all.begin() + lo, all.begin() + hi + 1);
    for (int i = 0; i < n; ++i) {
      WindowStage& st = w[i];
      sta::LibertyPort* dport = drvr_ports[lo + i];
      sta::LibertyPort* iport = in_ports[lo + i];
      const sta::RiseFall* in_rf = in_rfs[lo + i];
      sta::LibertyCell* cell = dport->libertyCell();
      const sta::LibertyPort* cur_out
          = static_cast<const sta::LibertyPort*>(dport)->scenePort(lib_ap);
      const sta::LibertyPort* cur_in
          = static_cast<const sta::LibertyPort*>(iport)->scenePort(lib_ap);
      if (cur_out == nullptr || cur_in == nullptr) {
        return false;
      }
      auto in_cap = [&](const sta::LibertyPort* ip) {
        return in_rf != nullptr ? ip->capacitance(in_rf, min_max)
                                : ip->capacitance();
      };
      st.cands.push_back(cell);
      st.outs.push_back(cur_out);
      st.cin.push_back(in_cap(cur_in));
      st.area.push_back(std::max(cell->area(), 1e-6f));
      if (!cell->isSequential()) {
        const float r_rise
            = cur_out->driveResistance(sta::RiseFall::rise(), min_max);
        const float r_fall
            = cur_out->driveResistance(sta::RiseFall::fall(), min_max);
        std::vector<std::tuple<float, std::string, sta::LibertyCell*>> extra;
        for (sta::LibertyCell* s : resizer_.getSwappableCells(cell)) {
          if (s == cell) {
            continue;
          }
          sta::LibertyCell* sc = s->sceneCell(lib_ap);
          if (sc == nullptr || s->area() > kMaxAreaRatio * cell->area()) {
            continue;
          }
          const sta::LibertyPort* so = sc->findLibertyPort(dport->name());
          const sta::LibertyPort* si = sc->findLibertyPort(iport->name());
          if (so == nullptr || si == nullptr
              || so->driveResistance(sta::RiseFall::rise(), min_max) > r_rise
              || so->driveResistance(sta::RiseFall::fall(), min_max) > r_fall) {
            continue;
          }
          extra.emplace_back(s->area(), std::string(s->name()), s);
        }
        std::ranges::sort(extra, [](const auto& a, const auto& b) {
          if (std::get<0>(a) != std::get<0>(b)) {
            return std::get<0>(a) < std::get<0>(b);
          }
          return std::get<1>(a) < std::get<1>(b);
        });
        for (const auto& e : extra) {
          if (static_cast<int>(st.cands.size()) > kMaxCandsPerStage) {
            break;
          }
          sta::LibertyCell* s = std::get<2>(e);
          sta::LibertyCell* sc = s->sceneCell(lib_ap);
          st.cands.push_back(s);
          st.outs.push_back(sc->findLibertyPort(dport->name()));
          st.cin.push_back(in_cap(sc->findLibertyPort(iport->name())));
          st.area.push_back(std::max(s->area(), 1e-6f));
        }
      }
    }
    for (int i = 0; i + 1 < n; ++i) {
      w[i].side_load = std::max(0.0f, w[i].load - w[i + 1].cin[0]);
    }
    // Upstream (outside-window) stage: fixed drive resistance and side fanout.
    float prev_drive = 0.0f;
    int ext_side_fanout = 0;
    if (lo > 0 && contiguous(lo - 1)) {
      const sta::LibertyPort* pp
          = static_cast<const sta::LibertyPort*>(drvr_ports[lo - 1])
                ->scenePort(lib_ap);
      if (pp != nullptr && all[lo - 1].drvr_rf != nullptr) {
        prev_drive = pp->driveResistance(all[lo - 1].drvr_rf, min_max);
      }
      ext_side_fanout = all[lo - 1].side_fanout;
    }

    auto stage_delay = [&](int i, int a, float load) {
      return w[i].drvr_rf != nullptr
                 ? static_cast<float>(resizer_.gateDelay(
                       w[i].outs[a], w[i].drvr_rf, load, scene, min_max))
                 : static_cast<float>(
                       resizer_.gateDelay(w[i].outs[a], load, scene, min_max));
    };
    auto drive_r = [&](int i, int a) {
      return w[i].drvr_rf != nullptr
                 ? w[i].outs[a]->driveResistance(w[i].drvr_rf, min_max)
                 : w[i].outs[a]->driveResistance(sta::RiseFall::rise(),
                                                 min_max);
    };
    auto area_pen = [&](int i, int a) {
      return kAreaPenalty * (w[i].area[a] / w[i].area[0] - 1.0f);
    };
    // Cost of choosing master a at stage i given master b at stage i-1
    // (i == 0: b is ignored, the upstream stage is fixed).
    auto in_cost = [&](int i, int b, int a) {
      const float dcin = std::max(0.0f, w[i].cin[a] - w[i].cin[0]);
      float c = area_pen(i, a);
      if (i == 0) {
        c += prev_drive * w[i].cin[a]
             + kSideWeight * prev_drive * dcin
                   * static_cast<float>(ext_side_fanout);
      } else {
        c += stage_delay(i - 1, b, w[i - 1].side_load + w[i].cin[a])
             + kSideWeight * drive_r(i - 1, b) * dcin
                   * static_cast<float>(w[i - 1].side_fanout);
      }
      return c;
    };
    auto eval = [&](const std::vector<int>& asg) {
      float c = 0.0f;
      for (int i = 0; i < n; ++i) {
        c += in_cost(i, i > 0 ? asg[i - 1] : 0, asg[i]);
      }
      c += stage_delay(n - 1, asg[n - 1], w[n - 1].load);
      return c;
    };

    // Viterbi: best[i][a] = min cost of stages 0..i-1 transitions ending in a.
    std::vector<std::vector<float>> best(n);
    std::vector<std::vector<int>> back(n);
    for (int i = 0; i < n; ++i) {
      const int ka = static_cast<int>(w[i].cands.size());
      best[i].assign(ka, 0.0f);
      back[i].assign(ka, 0);
      for (int a = 0; a < ka; ++a) {
        if (i == 0) {
          best[i][a] = in_cost(0, 0, a);
          continue;
        }
        float bc = std::numeric_limits<float>::infinity();
        int bb = 0;
        for (int b = 0; b < static_cast<int>(w[i - 1].cands.size()); ++b) {
          const float c = best[i - 1][b] + in_cost(i, b, a);
          if (c < bc) {
            bc = c;
            bb = b;
          }
        }
        best[i][a] = bc;
        back[i][a] = bb;
      }
    }
    float dp_cost = std::numeric_limits<float>::infinity();
    int last = 0;
    for (int a = 0; a < static_cast<int>(w[n - 1].cands.size()); ++a) {
      const float c = best[n - 1][a] + stage_delay(n - 1, a, w[n - 1].load);
      if (c < dp_cost) {
        dp_cost = c;
        last = a;
      }
    }
    std::vector<int> dp_asg(n, 0);
    dp_asg[n - 1] = last;
    for (int i = n - 1; i > 0; --i) {
      dp_asg[i - 1] = back[i][dp_asg[i]];
    }
    ++win_examined;
    const std::vector<int> zeros(n, 0);
    const float cur_cost = eval(zeros);
    if (cur_cost - dp_cost < kMinWindowGain) {
      return false;
    }
    ++win_with_gain;

    // Greedy reference: best single-stage change with the others untouched.
    std::vector<int> greedy_asg(n, 0);
    float greedy_cost = cur_cost;
    for (int i = 0; i < n; ++i) {
      for (int a = 1; a < static_cast<int>(w[i].cands.size()); ++a) {
        std::vector<int> t(n, 0);
        t[i] = a;
        const float c = eval(t);
        if (c < greedy_cost) {
          greedy_cost = c;
          greedy_asg = t;
        }
      }
    }
    if (greedy_asg != dp_asg) {
      ++win_joint_differs;
    }
    for (int i = 0; i < n; ++i) {
      if (dp_asg[i] != 0) {
        insts.push_back(w[i].inst);
        masters.push_back(w[i].cands[dp_asg[i]]);
      }
    }
    win_stages_changed += static_cast<int64_t>(insts.size());
    return !insts.empty();
  };

  sta::Slack wns_floor = 0.0;
  sta::Vertex* wns_vertex = nullptr;
  target_collector_->worstSlack(wns_floor, wns_vertex);
  const float setup_slack_margin = config_.setup_slack_margin;

  if (wns_vertex != nullptr && wns_floor < setup_slack_margin) {
    float cur_tns = totalNegativeSlack();
    for (int round = 0; round < kMaxRounds && kept < move_cap; ++round) {
      if (resizer_.overMaxArea()) {
        break;
      }
      ++rounds;
      const ViolatingEnds ends = collectViolatingEndpoints(setup_slack_margin);
      if (ends.empty()) {
        break;
      }

      // Rank drivers by slack-weighted count of violating paths through them.
      struct Bottleneck
      {
        std::string name;
        double weight{0.0};
        std::string end_name;  // worst violating endpoint through this driver
      };
      std::vector<Bottleneck> bottlenecks;
      std::unordered_map<const sta::Pin*, size_t> index_of;
      const int path_count
          = std::min(static_cast<int>(ends.size()), kTopPaths);
      for (int i = 0; i < path_count; ++i) {
        sta::Path* path = endpointWorstPath(ends[i].first);
        if (path == nullptr) {
          continue;
        }
        sta::PathExpanded expanded(path, sta_);
        const double weight = -static_cast<double>(ends[i].second);
        for (size_t k = expanded.startIndex(); k < expanded.size(); ++k) {
          const sta::Path* p = expanded.path(k);
          sta::Vertex* v = p->vertex(sta_);
          const sta::Pin* pin = p->pin(sta_);
          if (!v->isDriver(network_) || network_->isTopLevelPort(pin)) {
            continue;
          }
          auto [it, inserted] = index_of.emplace(pin, bottlenecks.size());
          if (inserted) {
            bottlenecks.push_back({network_->pathName(pin),
                                   0.0,
                                   network_->pathName(ends[i].first->pin())});
          }
          bottlenecks[it->second].weight += weight;
        }
      }
      std::ranges::stable_sort(
          bottlenecks, [](const Bottleneck& a, const Bottleneck& b) {
            if (a.weight != b.weight) {
              return a.weight > b.weight;
            }
            return a.name < b.name;
          });
      drivers_ranked += static_cast<int64_t>(bottlenecks.size());

      int round_kept = 0;
      const int driver_count
          = std::min(static_cast<int>(bottlenecks.size()), kTopDrivers);
      for (int d = 0; d < driver_count && kept < move_cap; ++d) {
        std::unordered_set<MoveType> rejected_types;
        {
          // Joint window move first; fall through to the stock attempts when
          // it finds no gain or is rejected.
          const sta::Pin* wpin = network_->findPin(bottlenecks[d].name.c_str());
          const sta::Pin* wend
              = network_->findPin(bottlenecks[d].end_name.c_str());
          Target wtarget;
          std::vector<sta::Instance*> winsts;
          std::vector<sta::LibertyCell*> wmasters;
          if (wpin != nullptr && makePinTarget(wpin, wns_floor, wtarget)
              && planWindow(wpin, wend, wtarget, winsts, wmasters)) {
            committer_.beginJournal();
            ++win_trials;
            bool applied = true;
            for (size_t m = 0; m < winsts.size(); ++m) {
              if (!resizer_.replaceCell(winsts[m], wmasters[m])) {
                applied = false;
                break;
              }
            }
            resizer_.updateParasiticsAndTiming();
            if (!applied) {
              committer_.restoreJournal();
              resizer_.updateParasiticsAndTiming();
            } else {
              sta::Slack wns = 0.0;
              sta::Vertex* wv = nullptr;
              target_collector_->worstSlack(wns, wv);
              const float tns = totalNegativeSlack();
              const bool wns_ok = sta::fuzzyGreaterEqual(wns, wns_floor);
              if (wns_ok && tns >= cur_tns + kMinTnsGain) {
                committer_.commitJournal();
                cur_tns = tns;
                ++kept;
                ++win_kept;
                ++round_kept;
                continue;
              }
              if (wns_ok) {
                ++win_rejected_tns;
              } else {
                ++win_rejected_wns;
              }
              committer_.restoreJournal();
              resizer_.updateParasiticsAndTiming();
            }
          }
        }
        for (int attempt = 0; attempt < kAttemptsPerDriver; ++attempt) {
          // Resolve by name: earlier trials may have replaced objects.
          const sta::Pin* pin = network_->findPin(bottlenecks[d].name.c_str());
          if (pin == nullptr) {
            break;
          }
          Target target;
          if (!makePinTarget(pin, wns_floor, target)) {
            break;
          }
          committer_.beginJournal();
          int changed = 0;
          std::optional<MoveType> accepted_type;
          ++trials;
          const bool moved = tryRepairTarget(
              target, 1, changed, &rejected_types, accepted_type);
          if (!moved) {
            committer_.restoreJournal();
            break;
          }
          resizer_.updateParasiticsAndTiming();
          sta::Slack wns = 0.0;
          sta::Vertex* wv = nullptr;
          target_collector_->worstSlack(wns, wv);
          const float tns = totalNegativeSlack();
          const bool wns_ok = sta::fuzzyGreaterEqual(wns, wns_floor);
          if (wns_ok && tns >= cur_tns + kMinTnsGain) {
            committer_.commitJournal();
            cur_tns = tns;
            ++kept;
            ++round_kept;
            break;
          }
          if (!wns_ok) {
            ++rejected_wns;
          } else {
            ++rejected_tns;
          }
          committer_.restoreJournal();
          resizer_.updateParasiticsAndTiming();
          if (accepted_type) {
            rejected_types.insert(*accepted_type);
          } else {
            break;
          }
        }
      }
      if (round_kept == 0) {
        break;
      }
    }
  }

  logger_->report("RSZ_EVOLVE window_dp_examined fired={}", win_examined);
  logger_->report("RSZ_EVOLVE window_dp_with_gain fired={}", win_with_gain);
  logger_->report("RSZ_EVOLVE window_joint_changed_vs_greedy fired={}",
                  win_joint_differs);
  logger_->report("RSZ_EVOLVE window_dp_stages_changed fired={}",
                  win_stages_changed);
  logger_->report("RSZ_EVOLVE window_dp_trials fired={}", win_trials);
  logger_->report("RSZ_EVOLVE window_dp_kept fired={}", win_kept);
  logger_->report("RSZ_EVOLVE window_dp_rejected_wns fired={}",
                  win_rejected_wns);
  logger_->report("RSZ_EVOLVE window_dp_rejected_tns fired={}",
                  win_rejected_tns);
  logger_->report("RSZ_EVOLVE bottleneck_rounds fired={}", rounds);
  logger_->report("RSZ_EVOLVE bottleneck_drivers_ranked fired={}",
                  drivers_ranked);
  logger_->report("RSZ_EVOLVE bottleneck_trials fired={}", trials);
  logger_->report("RSZ_EVOLVE bottleneck_kept fired={}", kept);
  logger_->report("RSZ_EVOLVE bottleneck_rejected_wns fired={}", rejected_wns);
  logger_->report("RSZ_EVOLVE bottleneck_rejected_tns fired={}", rejected_tns);
}

bool SetupLegacyPolicy::pathImproved(const sta::Slack end_slack,
                                     const sta::Slack worst_slack,
                                     const sta::Slack prev_end_slack,
                                     const sta::Slack prev_worst_slack) const
{
  return sta::fuzzyGreater(worst_slack, prev_worst_slack)
         || (sta::fuzzyEqual(worst_slack, prev_worst_slack)
             && sta::fuzzyGreater(end_slack, prev_end_slack));
}

}  // namespace rsz
