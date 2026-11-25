// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "MoveCandidate.hh"
#include "OptimizerTypes.hh"
#include "odb/geom.h"
#include "rsz/Resizer.hh"
#include "sta/NetworkClass.hh"

namespace sta {
class LibertyCell;
}  // namespace sta

namespace rsz {

// Candidate that inserts one buffer on the driver net and rewires a selected
// load subset to the buffer output.
//
// Unlike BufferCandidate (which uses the Rebuffer engine), SplitLoad
// performs a simpler insertion: it creates one buffer at drvr_loc_, reconnects
// the load pins in load_pins_ to the buffer output, and then optionally
// resizes the inserted buffer.  Useful for high-fanout nets where the full
// Rebuffer tree-search is too expensive.  Single-threaded only.
// Counters for the required-time-ordered fanout tree move.  Shared by all
// candidates and printed (then cleared) by ~SplitLoadGenerator.
struct FanoutTreeStats
{
  int64_t trees_built{0};
  int64_t buffers_inserted{0};
  int64_t sinks_isolated{0};
  int64_t stock_fallback{0};
};
FanoutTreeStats& fanoutTreeStats();

// One buffered group of a fanout tree.
struct FanoutTreeGroup
{
  std::unique_ptr<sta::PinSet> loads;
  odb::Point loc;
  sta::LibertyCell* buffer_cell{nullptr};
};

class SplitLoadCandidate : public MoveCandidate
{
 public:
  // === Construction =========================================================
  // Fanout-tree form: one buffer per group, most critical sinks stay direct.
  SplitLoadCandidate(Resizer& resizer,
                     const Target& target,
                     sta::Net* drvr_net,
                     std::vector<FanoutTreeGroup> groups);
  SplitLoadCandidate(Resizer& resizer,
                     const Target& target,
                     sta::Net* drvr_net,
                     sta::LibertyCell* buffer_cell,
                     const odb::Point& drvr_loc,
                     std::unique_ptr<sta::PinSet> load_pins);
  ~SplitLoadCandidate() override;

  // === MoveCandidate API ====================================================
  MoveResult apply() override;
  MoveType type() const override { return MoveType::kSplitLoad; }

 private:
  // === Split-buffer application helpers ====================================
  int resizeInsertedBuffer(sta::Instance* buffer) const;
  void invalidateAffectedParasitics(sta::Instance* buffer) const;
  MoveResult applySplitBuffer();
  MoveResult applyFanoutTree();

  // === Candidate state ======================================================
  sta::Net* drvr_net_{nullptr};
  sta::LibertyCell* buffer_cell_{nullptr};
  odb::Point drvr_loc_;
  std::unique_ptr<sta::PinSet> load_pins_;
  std::vector<FanoutTreeGroup> tree_groups_;
};

}  // namespace rsz
