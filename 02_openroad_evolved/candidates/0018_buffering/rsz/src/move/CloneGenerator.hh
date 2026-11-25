// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026-2026, The OpenROAD Authors

#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MoveCandidate.hh"
#include "MoveGenerator.hh"
#include "OptimizerTypes.hh"
#include "rsz/Resizer.hh"

namespace rsz {

// Builds gate-clone candidates for high-fanout combinational drivers.
// isApplicable() checks that the driver has enough fanout to benefit and
// that skip_gate_cloning is not set.  The generator partitions loads by
// slack criticality and produces one CloneCandidate.  Single-threaded only.
class CloneGenerator : public MoveGenerator
{
 public:
  // === Construction =========================================================
  explicit CloneGenerator(const GeneratorContext& context);
  ~CloneGenerator() override;

  // === MoveGenerator API ====================================================
  MoveType type() const override { return MoveType::kClone; }
  std::vector<std::unique_ptr<MoveCandidate>> generate(
      const Target& target) override;

 private:
  // Repeat requests for a shared high-fanout driver (the recovery phase
  // re-targets drivers after a rejected trial) rotate through criticality
  // partitioned variants: a replica that takes only the critical sinks.
  std::map<std::string, int> attempts_;
  int64_t variant_fired_{0};
  int64_t variant_drivers_{0};
  int64_t variant_loads_moved_{0};
};

}  // namespace rsz
