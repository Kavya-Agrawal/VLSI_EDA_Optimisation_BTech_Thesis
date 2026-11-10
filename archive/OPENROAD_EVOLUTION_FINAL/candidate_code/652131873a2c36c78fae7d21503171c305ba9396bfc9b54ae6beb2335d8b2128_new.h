// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72897347;
  double density_weight = 0.56521952;
  double prefix_weight = 0.18491952;
  double neighborhood_weight = 0.33932987;
  double late_weight = 0.10945005;
  double critical_weight = 0.28493580;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
