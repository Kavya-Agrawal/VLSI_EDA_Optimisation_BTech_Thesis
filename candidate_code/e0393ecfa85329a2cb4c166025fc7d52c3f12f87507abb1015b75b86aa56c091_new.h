// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17409066;
  double density_weight = 0.49440799;
  double prefix_weight = 0.47690072;
  double neighborhood_weight = 0.19864189;
  double late_weight = 0.10154577;
  double critical_weight = 0.49392732;
  unsigned budget = 40;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
