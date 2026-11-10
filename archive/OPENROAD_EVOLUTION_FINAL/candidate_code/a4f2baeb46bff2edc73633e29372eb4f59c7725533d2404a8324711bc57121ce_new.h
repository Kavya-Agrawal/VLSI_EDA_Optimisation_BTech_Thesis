// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89235353;
  double density_weight = 0.00280132;
  double prefix_weight = 0.06491453;
  double neighborhood_weight = 0.21597122;
  double late_weight = 0.19094899;
  double critical_weight = 0.42334362;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
