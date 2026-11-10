// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71277348;
  double density_weight = 0.42477409;
  double prefix_weight = 0.42396393;
  double neighborhood_weight = 0.27212902;
  double late_weight = 0.01963578;
  double critical_weight = 0.02089520;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
