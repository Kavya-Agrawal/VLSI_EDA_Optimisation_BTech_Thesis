// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51194083;
  double density_weight = 0.09027911;
  double prefix_weight = 0.04686134;
  double neighborhood_weight = 0.14384245;
  double late_weight = 0.07542146;
  double critical_weight = 0.18917033;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
