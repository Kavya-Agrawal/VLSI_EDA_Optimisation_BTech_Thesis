// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023-2025, The OpenROAD Authors

#include "RecoverPower.hh"

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "db_sta/dbNetwork.hh"
#include "db_sta/dbSta.hh"
#include "est/EstimateParasitics.h"
#include "odb/db.h"
#include "rsz/Resizer.hh"
#include "sta/ContainerHelpers.hh"
#include "sta/Delay.hh"
#include "sta/Graph.hh"
#include "sta/GraphClass.hh"
#include "sta/GraphDelayCalc.hh"
#include "sta/Liberty.hh"
#include "sta/LibertyClass.hh"
#include "sta/NetworkClass.hh"
#include "sta/Path.hh"
#include "sta/PathExpanded.hh"
#include "sta/Sdc.hh"
#include "sta/TimingArc.hh"
#include "utl/Logger.h"


// Algorithms below belong to this production translation unit.
#include "LearningMode.h"
#include "LearningPolicyConfig.h"

// BEGIN INTEGRATED KERNEL LazyQueue
// SPDX-License-Identifier: BSD-3-Clause
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace ord::learning {
// Generation stamps discard outdated priorities without in-place heap mutation.
class LazyQueue
{
 public:
  void update(std::size_t id, double priority)
  {
    if (!std::isfinite(priority)) {
      throw std::invalid_argument("Priority must be finite");
    }
    auto& version = versions_[id];
    ++version;
    queue_.push({priority, id, version});
  }

  void erase(std::size_t id)
  {
    // Keep the generation counter to prevent ABA after reinsertion.
    ++versions_[id];
  }

  std::optional<std::pair<std::size_t, double>> pop()
  {
    while (!queue_.empty()) {
      const auto entry = queue_.top();
      queue_.pop();
      if (versions_.at(entry.id) != entry.version) {
        continue;
      }
      ++versions_[entry.id];
      return std::make_pair(entry.id, entry.priority);
    }
    return std::nullopt;
  }

 private:
  struct Entry
  {
    double priority;
    std::size_t id;
    std::uint64_t version;
    bool operator<(const Entry& other) const
    {
      if (priority != other.priority) {
        return priority < other.priority;
      }
      return id > other.id;
    }
  };
  std::priority_queue<Entry> queue_;
  std::unordered_map<std::size_t, std::uint64_t> versions_;
};
}  // namespace ord::learning
// END INTEGRATED KERNEL LazyQueue

// BEGIN INTEGRATED KERNEL RollbackSet
// SPDX-License-Identifier: BSD-3-Clause
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ord::learning {
// Speculative clustering can restore connectivity without copying the forest.
// Path compression is intentionally omitted so each union has a bounded log.
class RollbackSet
{
 public:
  explicit RollbackSet(std::size_t size) : parent_(size), sizes_(size, 1)
  {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  std::size_t find(std::size_t node) const
  {
    if (node >= parent_.size()) {
      throw std::out_of_range("RollbackSet node");
    }
    while (parent_[node] != node) {
      node = parent_[node];
    }
    return node;
  }

  std::size_t checkpoint() const { return history_.size(); }

  bool unite(std::size_t a, std::size_t b)
  {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (sizes_[a] < sizes_[b]) {
      std::swap(a, b);
    }
    history_.push_back({a, b, sizes_[a]});
    parent_[b] = a;
    sizes_[a] += sizes_[b];
    return true;
  }

  void rollback(std::size_t checkpoint)
  {
    if (checkpoint > history_.size()) {
      throw std::out_of_range("RollbackSet future checkpoint");
    }
    while (history_.size() > checkpoint) {
      const auto record = history_.back();
      history_.pop_back();
      parent_[record.child] = record.child;
      sizes_[record.parent] = record.old_size;
    }
  }

  std::size_t componentSize(std::size_t node) const { return sizes_[find(node)]; }

 private:
  struct Record
  {
    std::size_t parent;
    std::size_t child;
    std::size_t old_size;
  };
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> sizes_;
  std::vector<Record> history_;
};
}  // namespace ord::learning
// END INTEGRATED KERNEL RollbackSet

namespace rsz {

using std::pair;
using std::string;
using std::vector;

using utl::RSZ;

RecoverPower::RecoverPower(Resizer* resizer)
    : resizer_(resizer), bad_vertices_(resizer->graph_)
{
}

void RecoverPower::init()
{
  logger_ = resizer_->logger_;
  dbStaState::init(resizer_->sta_);
  db_network_ = resizer_->db_network_;
  estimate_parasitics_ = resizer_->estimate_parasitics_;
  initial_design_area_ = resizer_->computeDesignArea();
}

bool RecoverPower::recoverPower(const float recover_power_percent, bool verbose)
{
  bool recovered = false;
  init();
  constexpr int digits = 3;
  resize_count_ = 0;

  // Sort failing endpoints by slack.
  sta::VertexSet& endpoints = sta_->endpoints();
  sta::VertexSeq ends_with_slack;
  for (sta::Vertex* end : endpoints) {
    const sta::Slack end_slack = sta_->slack(end, max_);
    if (end_slack > setup_slack_margin_
        && end_slack < setup_slack_max_margin_) {
      ends_with_slack.push_back(end);
    }
  }

  // LEARN-RSZ-02: snapshot slacks before sorting; comparator is pure.
  if (ord::learning::enabled()) {
    std::vector<std::pair<sta::Slack, sta::Vertex*>> cached;
    cached.reserve(ends_with_slack.size());
    for (auto* vertex : ends_with_slack) {
      cached.emplace_back(sta_->slack(vertex, max_), vertex);
    }
    std::stable_sort(cached.begin(), cached.end(), [](const auto& a, const auto& b) {
      return a.first > b.first;
    });
    for (std::size_t i = 0; i < cached.size(); ++i) {
      ends_with_slack[i] = cached[i].second;
    }
  } else {
    std::ranges::sort(ends_with_slack,
                      [this](sta::Vertex* end1, sta::Vertex* end2) {
                        return sta_->slack(end1, max_) > sta_->slack(end2, max_);
                      });
  }
  debugPrint(logger_,
             RSZ,
             "recover_power",
             1,
             "Candidate paths {}/{} {}%",
             ends_with_slack.size(),
             endpoints.size(),
             int(ends_with_slack.size() / double(endpoints.size()) * 100));

  int max_end_count = ends_with_slack.size() * recover_power_percent;
  // As long as we are here fix at least one path
  max_end_count = std::max(max_end_count, 1);

  sta::Slack worst_slack_before;
  sta::Vertex* worst_vertex;
  sta_->worstSlack(max_, worst_slack_before, worst_vertex);

  if (max_end_count > 5 * max_print_interval_) {
    print_interval_ = max_print_interval_;
  } else {
    print_interval_ = min_print_interval_;
  }

  printProgress(0, false, false);

  int end_index = 0;
  int failed_move_threshold = 0;
  est::IncrementalParasiticsGuard guard(estimate_parasitics_);
  for (sta::Vertex* end : ends_with_slack) {
    resizer_->journalBegin();
    const sta::Slack end_slack_before = sta_->slack(end, max_);
    sta::Slack worst_slack_after;
    //=====================================================================
    // Just a counter to know when to break out
    end_index++;
    debugPrint(logger_,
               RSZ,
               "recover_power",
               2,
               "Doing {} / {}",
               end_index,
               max_end_count);
    if (verbose || end_index == 1) {
      printProgress(end_index, false, false);
    }

    if (end_index > max_end_count) {
      resizer_->journalEnd();
      break;
    }
    //=====================================================================
    sta::Path* end_path = sta_->vertexWorstSlackPath(end, max_);
    sta::Vertex* const changed = recoverPower(end_path, end_slack_before);
    if (changed) {
      estimate_parasitics_->updateParasitics();
      sta_->findRequireds();
      const sta::Slack end_slack_after = sta_->slack(end, max_);

      sta_->worstSlack(max_, worst_slack_after, worst_vertex);

      const float worst_slack_percent = fabs(
          (worst_slack_before - worst_slack_after) / worst_slack_before * 100);
      const bool better
          = (worst_slack_percent < 0.0001
             || (worst_slack_before > 0
                 && worst_slack_after / worst_slack_before > 0.5));

      debugPrint(logger_,
                 RSZ,
                 "recover_power",
                 2,
                 "slack = {} worst_slack = {} better = {}",
                 sta::delayAsString(end_slack_after, digits, sta_),
                 sta::delayAsString(worst_slack_after, digits, sta_),
                 better ? "save" : "");

      if (better) {
        failed_move_threshold = 0;
        resizer_->journalEnd();
        resize_count_++;
        debugPrint(logger_,
                   RSZ,
                   "recover_power",
                   2,
                   "{}/{} Resize for power Slack change {} -> {}",
                   end_index,
                   ends_with_slack.size(),
                   sta::delayAsString(worst_slack_before, digits, sta_),
                   sta::delayAsString(worst_slack_after, digits, sta_));
        if (resizer_->overMaxArea()) {
          break;
        }
      } else {
        // Save the vertex to avoid trying it again.
        bad_vertices_.insert(changed);
        // Undo the change here.
        ++failed_move_threshold;
        if (failed_move_threshold > failed_move_threshold_limit_) {
          logger_->info(RSZ,
                        142,
                        "{} successive tries yielded negative slack. Ending "
                        "power recovery",
                        failed_move_threshold_limit_);
          resizer_->journalEnd();
          resize_count_++;
          break;
        }
        resizer_->journalRestore();
        debugPrint(logger_,
                   RSZ,
                   "recover_power",
                   2,
                   "{}/{} Undo resize for power Slack change {} -> {}",
                   end_index,
                   ends_with_slack.size(),
                   sta::delayAsString(worst_slack_before, digits, sta_),
                   sta::delayAsString(worst_slack_after, digits, sta_));
      }
    } else {
      resizer_->journalEnd();
    }
  }

  printProgress(end_index, true, true);

  bad_vertices_.clear();

  // TODO: Add the appropriate metric here
  // logger_->metric("design__instance__count__setup_buffer",
  // inserted_buffer_count_);
  if (resize_count_ > 0) {
    recovered = true;
    logger_->info(RSZ, 141, "Resized {} instances.", resize_count_);
  }
  if (resizer_->overMaxArea()) {
    logger_->error(RSZ, 125, "max utilization reached.");
  }

  return recovered;
}

// For testing.
sta::Vertex* RecoverPower::recoverPower(const sta::Pin* end_pin)
{
  init();
  resize_count_ = 0;

  sta::Vertex* vertex = graph_->pinLoadVertex(end_pin);
  const sta::Slack slack = sta_->slack(vertex, max_);
  const sta::Path* path = sta_->vertexWorstSlackPath(vertex, max_);
  sta::Vertex* drvr_vertex;

  {
    est::IncrementalParasiticsGuard guard(estimate_parasitics_);
    drvr_vertex = recoverPower(path, slack);
  }
  // No accept/reject journal here: a returned vertex is one kept downsize.
  if (drvr_vertex != nullptr) {
    resize_count_++;
  }

  if (resize_count_ > 0) {
    logger_->info(RSZ, 3111, "Resized {} instances.", resize_count_);
  }
  return drvr_vertex;
}

// This is the main routine for recovering power.
sta::Vertex* RecoverPower::recoverPower(const sta::Path* path,
                                        const sta::Slack path_slack)
{
  sta::PathExpanded expanded(path, sta_);
  sta::Vertex* changed = nullptr;

  if (expanded.size() > 1) {
    const int path_length = expanded.size();
    vector<pair<int, sta::Delay>> load_delays;
    const int start_index = expanded.startIndex();
    const auto dcalc_ap_index = path->dcalcAnalysisPtIndex(sta_);
    const int lib_ap = path->scene(sta_)->libertyIndex(path->minMax(sta_));
    // Find load delay for each gate in the path.
    for (int i = start_index; i < path_length; i++) {
      const sta::Path* path = expanded.path(i);
      const sta::Vertex* path_vertex = path->vertex(sta_);
      const sta::Pin* path_pin = path->pin(sta_);
      if (i > 0 && path_vertex->isDriver(network_)
          && !network_->isTopLevelPort(path_pin)) {
        const sta::TimingArc* prev_arc = path->prevArc(sta_);
        const sta::TimingArc* corner_arc = prev_arc->sceneArc(lib_ap);
        const sta::Edge* prev_edge = path->prevEdge(sta_);
        const sta::Delay load_delay
            = graph_->arcDelay(prev_edge, prev_arc, dcalc_ap_index)
              // Remove intrinsic delay to find load dependent delay.
              - corner_arc->intrinsicDelay();
        load_delays.emplace_back(i, load_delay);
        debugPrint(logger_,
                   RSZ,
                   "recover_power",
                   3,
                   "{} load_delay = {}",
                   path_vertex->name(network_),
                   delayAsString(load_delay, 3, sta_));
      }
    }

    // Sort the delays for any specific path. This way we can pick the fastest
    // delay and downsize that cell to achieve our goal instead of messing with
    // too many cells.
    std::ranges::sort(
        load_delays,

        [](const pair<int, sta::Delay>& pair1,
           const pair<int, sta::Delay>& pair2) {
          return pair1.second > pair2.second
                 || (pair1.second == pair2.second && pair1.first < pair2.first);
        });
    for (const auto& [drvr_index, ignored] : load_delays) {
      const sta::Path* drvr_path = expanded.path(drvr_index);
      sta::Vertex* drvr_vertex = drvr_path->vertex(sta_);
      // If we already tried this vertex and got a worse result, skip it.
      if (bad_vertices_.contains(drvr_vertex)) {
        continue;
      }
      const sta::Pin* drvr_pin = drvr_vertex->pin();
      const sta::LibertyPort* drvr_port = network_->libertyPort(drvr_pin);
      const sta::LibertyCell* drvr_cell
          = drvr_port ? drvr_port->libertyCell() : nullptr;
      const int fanout = this->fanout(drvr_vertex);
      debugPrint(logger_,
                 RSZ,
                 "recover_power",
                 3,
                 "{} {} fanout = {}",
                 network_->pathName(drvr_pin),
                 drvr_cell ? drvr_cell->name() : "none",
                 fanout);
      if (downsizeDrvr(drvr_path, drvr_index, &expanded, true, path_slack)) {
        changed = drvr_vertex;
        break;
      }
    }
  }
  return changed;
}

bool RecoverPower::downsizeDrvr(const sta::Path* drvr_path,
                                const int drvr_index,
                                sta::PathExpanded* expanded,
                                const bool only_same_size_swap,
                                const sta::Slack path_slack)
{
  const sta::Pin* drvr_pin = drvr_path->pin(this);
  sta::Instance* drvr = network_->instance(drvr_pin);
  const float load_cap = graph_delay_calc_->loadCap(
      drvr_pin, drvr_path->scene(sta_), drvr_path->minMax(sta_));
  const sta::TimingArc* in_arc = drvr_path->prevArc(sta_);
  const sta::LibertyPort* in_port = in_arc ? in_arc->from() : nullptr;
  if (in_port == nullptr) {
    return false;
  }
  if (!resizer_->dontTouch(drvr)) {
    float prev_drive = 0.0;
    if (drvr_index >= 2) {
      const int prev_drvr_index = drvr_index - 2;
      const sta::Path* prev_drvr_path = expanded->path(prev_drvr_index);
      const sta::Pin* prev_drvr_pin = prev_drvr_path->pin(sta_);
      const sta::LibertyPort* prev_drvr_port
          = network_->libertyPort(prev_drvr_pin);
      if (prev_drvr_port) {
        prev_drive = prev_drvr_port->driveResistance();
      }
    }
    const sta::LibertyPort* drvr_port = network_->libertyPort(drvr_pin);
    const sta::LibertyCell* downsize = downsizeCell(in_port,
                                                    drvr_port,
                                                    load_cap,
                                                    prev_drive,
                                                    drvr_path->scene(sta_),
                                                    drvr_path->minMax(sta_),
                                                    only_same_size_swap,
                                                    path_slack);
    if (downsize != nullptr) {
      debugPrint(logger_,
                 RSZ,
                 "recover_power",
                 3,
                 "resize {} {} -> {}",
                 network_->pathName(drvr_pin),
                 drvr_port->libertyCell()->name(),
                 downsize->name());
      if (resizer_->replaceCell(drvr, downsize, true)) {
        // Counted by the caller only if the move is kept (journalEnd).
        return true;
      }
    }
  }
  return false;
}

bool RecoverPower::meetsSizeCriteria(const sta::LibertyCell* cell,
                                     const sta::LibertyCell* candidate,
                                     const bool match_size)
{
  if (!match_size) {
    return true;
  }
  const odb::dbMaster* candidate_cell = db_network_->staToDb(candidate);
  const odb::dbMaster* curr_cell = db_network_->staToDb(cell);
  return candidate_cell->getWidth() <= curr_cell->getWidth()
         && candidate_cell->getHeight() == curr_cell->getHeight();
}

sta::LibertyCell* RecoverPower::downsizeCell(const sta::LibertyPort* in_port,
                                             const sta::LibertyPort* drvr_port,
                                             const float load_cap,
                                             const float prev_drive,
                                             const sta::Scene* scene,
                                             const sta::MinMax* min_max,
                                             const bool match_size,
                                             const sta::Slack path_slack)
{
  const int lib_ap = scene->libertyIndex(min_max);
  sta::LibertyCell* cell = drvr_port->libertyCell();
  sta::LibertyCellSeq swappable_cells = resizer_->getSwappableCells(cell);
  constexpr double delay_margin = 1.5;  // Prevent overly aggressive downsizing

  if (!swappable_cells.empty()) {
    const std::string& in_port_name = in_port->name();
    const std::string& drvr_port_name = drvr_port->name();
    sta::sort(
        &swappable_cells,
        [=, this](const sta::LibertyCell* cell1,
                  const sta::LibertyCell* cell2) {
          const sta::LibertyPort* port1
              = const_cast<const sta::LibertyPort*>(
                    cell1->findLibertyPort(drvr_port_name))
                    ->scenePort(lib_ap);
          const sta::LibertyPort* port2
              = const_cast<const sta::LibertyPort*>(
                    cell2->findLibertyPort(drvr_port_name))
                    ->scenePort(lib_ap);
          const float drive1 = port1->driveResistance();
          const float drive2 = port2->driveResistance();
          const sta::ArcDelay intrinsic1 = port1->intrinsicDelay(this);
          const sta::ArcDelay intrinsic2 = port2->intrinsicDelay(this);
          return (std::tie(drive1, intrinsic2) < std::tie(drive2, intrinsic1));
        });
    const float drive = drvr_port->scenePort(lib_ap)->driveResistance();
    const float delay
        = resizer_->gateDelay(drvr_port, load_cap, scene, min_max)
          + (prev_drive * in_port->scenePort(lib_ap)->capacitance());

    sta::LibertyCell* best_cell = nullptr;
    for (sta::LibertyCell* swappable : swappable_cells) {
      const sta::LibertyCell* swappable_corner = swappable->sceneCell(lib_ap);
      const sta::LibertyPort* swappable_drvr
          = swappable_corner->findLibertyPort(drvr_port_name);
      const sta::LibertyPort* swappable_input
          = swappable_corner->findLibertyPort(in_port_name);
      const float current_drive = swappable_drvr->driveResistance();
      // Include delay of previous driver into swappable gate.
      const float current_delay
          = resizer_->gateDelay(swappable_drvr, load_cap, scene, min_max)
            + prev_drive * swappable_input->capacitance();

      if (!resizer_->dontUse(swappable) && current_drive > drive
          && current_delay > delay
          && (current_delay - delay) * delay_margin < path_slack  // add margin
          && meetsSizeCriteria(cell, swappable, match_size)) {
        best_cell = swappable;
      }
    }
    if (best_cell != nullptr) {
      return best_cell;
    }
  }
  return nullptr;
}

int RecoverPower::fanout(sta::Vertex* vertex)
{
  int fanout = 0;
  sta::VertexOutEdgeIterator edge_iter(vertex, graph_);
  while (edge_iter.hasNext()) {
    edge_iter.next();
    fanout++;
  }
  return fanout;
}

void RecoverPower::printProgress(int iteration, bool force, bool end) const
{
  const bool start = iteration == 0;

  if (start && !end) {
    logger_->report("Iteration |   Area    |  Resized |   WNS    | Endpt");
    logger_->report("---------------------------------------------------");
  }

  if (iteration % print_interval_ == 0 || force || end) {
    sta::Slack wns;
    sta::Vertex* worst_vertex;
    sta_->worstSlack(max_, wns, worst_vertex);

    std::string itr_field = fmt::format("{}", iteration);
    if (end) {
      itr_field = "final";
    }

    const double design_area = resizer_->computeDesignArea();
    const double area_growth = design_area - initial_design_area_;
    double area_growth_percent = std::numeric_limits<double>::infinity();
    if (std::abs(initial_design_area_) > 0.0) {
      area_growth_percent = area_growth / initial_design_area_ * 100.0;
    }

    logger_->report(
        "{: >9s} | {: >+8.1f}% | {: >8d} | {: >8s} | {}",
        itr_field,
        area_growth_percent,
        resize_count_,
        delayAsString(wns, 3, sta_),
        worst_vertex != nullptr ? worst_vertex->name(network_) : "");
  }

  if (end) {
    logger_->report("---------------------------------------------------");
  }
}

}  // namespace rsz
