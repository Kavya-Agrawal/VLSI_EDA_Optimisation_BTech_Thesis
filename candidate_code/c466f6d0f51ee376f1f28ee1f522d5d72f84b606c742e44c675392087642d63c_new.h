// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62978894;
  double density_weight = 0.27074327;
  double prefix_weight = 0.05149958;
  double neighborhood_weight = 0.26920072;
  double late_weight = 0.15584477;
  double critical_weight = 0.21597052;
  unsigned budget = 36;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
