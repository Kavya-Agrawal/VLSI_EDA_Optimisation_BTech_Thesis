// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#include "SetupLegacyPolicy.hh"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
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
#include "sta/GraphClass.hh"
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
  // The beam search replaces the first-improving greedy recovery.
  runBeamRecovery();
}

void SetupLegacyPolicy::runGreedyTnsRecovery()
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
            bottlenecks.push_back({network_->pathName(pin), 0.0});
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

  logger_->report("RSZ_EVOLVE bottleneck_rounds fired={}", rounds);
  logger_->report("RSZ_EVOLVE bottleneck_drivers_ranked fired={}",
                  drivers_ranked);
  logger_->report("RSZ_EVOLVE bottleneck_trials fired={}", trials);
  logger_->report("RSZ_EVOLVE bottleneck_kept fired={}", kept);
  logger_->report("RSZ_EVOLVE bottleneck_rejected_wns fired={}", rejected_wns);
  logger_->report("RSZ_EVOLVE bottleneck_rejected_tns fired={}", rejected_tns);
}

void SetupLegacyPolicy::runBeamRecovery()
{
  // Measured depth-2 beam search over coupled sizing sequences on data-path
  // stages.  Seeds are ranked by slack-weighted endpoint coverage times arc
  // delay (launch-Q to D data arcs only).  Each seed is tried alone and
  // paired with its upstream / downstream path driver inside nested ECO
  // journals; only the best sequence per round is replayed and committed.
  constexpr int kTopPaths = 400;
  constexpr int kSeeds = 8;
  constexpr int kMaxRounds = 12;
  constexpr float kMinTnsGain = 0.5e-12f;
  constexpr float kGuardSlack = -1.0e-12f;
  constexpr float kGuardWindow = 50.0e-12f;

  int64_t seeds_ranked = 0;
  int64_t clock_arcs_skipped = 0;
  int64_t rounds = 0;
  int64_t single_trials = 0;
  int64_t pair_trials = 0;
  int64_t committed_single = 0;
  int64_t committed_pair = 0;
  int64_t rejected_wns = 0;
  int64_t rejected_tns = 0;
  int64_t rejected_guard = 0;
  int64_t replay_mismatch = 0;

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

  sta::Slack wns_floor = 0.0;
  sta::Vertex* wns_vertex = nullptr;
  target_collector_->worstSlack(wns_floor, wns_vertex);
  const float setup_slack_margin = config_.setup_slack_margin;

  struct Seed
  {
    std::string name;
    std::string up;
    std::string down;
    double weight{0.0};
  };
  struct Cand
  {
    float tns{0.0f};
    std::string a_name;
    std::optional<MoveType> a_avoid;
    std::string b_name;
  };

  // Endpoints at or above the guard slack must not fall below it.
  auto guardBaseline = [&]() {
    std::unordered_set<sta::Vertex*> base;
    for (const auto& [v, s] : collectViolatingEndpoints(kGuardWindow)) {
      if (s >= kGuardSlack) {
        base.insert(v);
      }
    }
    return base;
  };
  auto guardOk = [&](const std::unordered_set<sta::Vertex*>& base) {
    for (const auto& [v, s] : collectViolatingEndpoints(kGuardWindow)) {
      if (s < kGuardSlack && base.contains(v)) {
        return false;
      }
    }
    return true;
  };

  // Apply one single-stage move at a named driver pin.
  auto applyStep = [&](const std::string& name,
                       const std::optional<MoveType>& avoid,
                       std::optional<MoveType>& used) {
    const sta::Pin* pin = network_->findPin(name.c_str());
    if (pin == nullptr) {
      return false;
    }
    Target target;
    if (!makePinTarget(pin, wns_floor, target)) {
      return false;
    }
    std::unordered_set<MoveType> rejected;
    if (avoid) {
      rejected.insert(*avoid);
    }
    int changed = 0;
    return tryRepairTarget(target, 1, changed, &rejected, used);
  };

  if (wns_vertex != nullptr && wns_floor < setup_slack_margin) {
    float cur_tns = totalNegativeSlack();
    for (int round = 0;
         round < kMaxRounds && committed_single + committed_pair < move_cap;
         ++round) {
      if (resizer_.overMaxArea()) {
        break;
      }
      ++rounds;
      const ViolatingEnds ends = collectViolatingEndpoints(setup_slack_margin);
      if (ends.empty()) {
        break;
      }

      // Rank seeds over data arcs only.
      std::vector<Seed> seeds;
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
        std::vector<size_t> drivers;
        for (size_t k = expanded.startIndex(); k < expanded.size(); ++k) {
          const sta::Path* p = expanded.path(k);
          const sta::Pin* pin = p->pin(sta_);
          if (!p->vertex(sta_)->isDriver(network_)
              || network_->isTopLevelPort(pin)) {
            continue;
          }
          drivers.push_back(k);
        }
        for (size_t di = 0; di < drivers.size(); ++di) {
          const size_t k = drivers[di];
          const sta::Path* p = expanded.path(k);
          if (p->isClock(sta_) || k == 0) {
            ++clock_arcs_skipped;
            continue;
          }
          const double delay
              = static_cast<double>(p->arrival())
                - static_cast<double>(expanded.path(k - 1)->arrival());
          if (delay <= 0.0) {
            continue;
          }
          const sta::Pin* pin = p->pin(sta_);
          auto [it, inserted] = index_of.emplace(pin, seeds.size());
          if (inserted) {
            Seed s;
            s.name = network_->pathName(pin);
            if (di > 0) {
              s.up = network_->pathName(
                  expanded.path(drivers[di - 1])->pin(sta_));
            }
            if (di + 1 < drivers.size()) {
              s.down = network_->pathName(
                  expanded.path(drivers[di + 1])->pin(sta_));
            }
            seeds.push_back(std::move(s));
          }
          seeds[it->second].weight += weight * delay;
        }
      }
      std::ranges::stable_sort(seeds, [](const Seed& a, const Seed& b) {
        if (a.weight != b.weight) {
          return a.weight > b.weight;
        }
        return a.name < b.name;
      });
      seeds_ranked += static_cast<int64_t>(seeds.size());

      const auto base = guardBaseline();
      std::optional<Cand> best;

      // Evaluate the current (journaled) netlist against all acceptance rules.
      auto evaluate = [&](float& tns_out) {
        resizer_.updateParasiticsAndTiming();
        sta::Slack wns = 0.0;
        sta::Vertex* wv = nullptr;
        target_collector_->worstSlack(wns, wv);
        tns_out = totalNegativeSlack();
        if (!sta::fuzzyGreaterEqual(wns, wns_floor)) {
          ++rejected_wns;
          return false;
        }
        if (tns_out < cur_tns + kMinTnsGain) {
          ++rejected_tns;
          return false;
        }
        if (!guardOk(base)) {
          ++rejected_guard;
          return false;
        }
        return true;
      };

      const int seed_count = std::min(static_cast<int>(seeds.size()), kSeeds);
      for (int d = 0; d < seed_count; ++d) {
        std::optional<MoveType> first_used;
        for (int variant = 0; variant < 2; ++variant) {
          std::optional<MoveType> avoid;
          if (variant == 1) {
            if (!first_used) {
              break;
            }
            avoid = first_used;
          }
          committer_.beginJournal();
          std::optional<MoveType> used;
          if (!applyStep(seeds[d].name, avoid, used)) {
            committer_.restoreJournal();
            break;
          }
          if (variant == 0) {
            first_used = used;
          }
          ++single_trials;
          float tns = 0.0f;
          if (evaluate(tns) && (!best || tns > best->tns)) {
            best = Cand{tns, seeds[d].name, avoid, ""};
          }
          for (const std::string* partner : {&seeds[d].up, &seeds[d].down}) {
            if (partner->empty()) {
              continue;
            }
            committer_.beginJournal();
            std::optional<MoveType> used_b;
            if (applyStep(*partner, std::nullopt, used_b)) {
              ++pair_trials;
              if (evaluate(tns) && (!best || tns > best->tns)) {
                best = Cand{tns, seeds[d].name, avoid, *partner};
              }
            }
            committer_.restoreJournal();
            resizer_.updateParasiticsAndTiming();
          }
          committer_.restoreJournal();
          resizer_.updateParasiticsAndTiming();
        }
      }
      if (!best) {
        break;
      }

      // Replay and commit the single best sequence of this round.
      committer_.beginJournal();
      std::optional<MoveType> used;
      bool ok = applyStep(best->a_name, best->a_avoid, used);
      if (ok && !best->b_name.empty()) {
        std::optional<MoveType> used_b;
        ok = applyStep(best->b_name, std::nullopt, used_b);
      }
      float tns = 0.0f;
      sta::Slack wns = 0.0;
      if (ok) {
        resizer_.updateParasiticsAndTiming();
        sta::Vertex* wv = nullptr;
        target_collector_->worstSlack(wns, wv);
        tns = totalNegativeSlack();
        ok = sta::fuzzyGreaterEqual(wns, wns_floor)
             && tns >= cur_tns + kMinTnsGain && guardOk(base);
      }
      if (!ok) {
        ++replay_mismatch;
        committer_.restoreJournal();
        resizer_.updateParasiticsAndTiming();
        break;
      }
      committer_.commitJournal();
      wns_floor = std::max(wns_floor, wns);
      cur_tns = tns;
      if (best->b_name.empty()) {
        ++committed_single;
      } else {
        ++committed_pair;
      }
    }
  }

  logger_->report("RSZ_EVOLVE beam_rounds fired={}", rounds);
  logger_->report("RSZ_EVOLVE beam_seeds_ranked fired={}", seeds_ranked);
  logger_->report("RSZ_EVOLVE beam_clock_arcs_skipped fired={}",
                  clock_arcs_skipped);
  logger_->report("RSZ_EVOLVE beam_single_trials fired={}", single_trials);
  logger_->report("RSZ_EVOLVE beam_pair_trials fired={}", pair_trials);
  logger_->report("RSZ_EVOLVE beam_committed_single fired={}",
                  committed_single);
  logger_->report("RSZ_EVOLVE beam_committed_pair fired={}", committed_pair);
  logger_->report("RSZ_EVOLVE beam_rejected_wns fired={}", rejected_wns);
  logger_->report("RSZ_EVOLVE beam_rejected_tns fired={}", rejected_tns);
  logger_->report("RSZ_EVOLVE beam_rejected_guard fired={}", rejected_guard);
  logger_->report("RSZ_EVOLVE beam_replay_mismatch fired={}", replay_mismatch);
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
