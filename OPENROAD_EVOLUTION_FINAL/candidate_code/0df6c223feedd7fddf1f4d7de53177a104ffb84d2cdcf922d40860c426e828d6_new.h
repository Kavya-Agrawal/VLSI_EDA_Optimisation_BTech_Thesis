// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72441551;
  double density_weight = 0.05243236;
  double prefix_weight = 0.06206933;
  double neighborhood_weight = 0.31068621;
  double late_weight = 0.22716171;
  double critical_weight = 0.10388762;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
