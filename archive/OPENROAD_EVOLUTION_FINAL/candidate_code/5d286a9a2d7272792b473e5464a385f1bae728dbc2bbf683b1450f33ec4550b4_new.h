// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56939962;
  double density_weight = 0.40080804;
  double prefix_weight = 0.32368938;
  double neighborhood_weight = 0.03815218;
  double late_weight = 0.04060307;
  double critical_weight = 0.47329310;
  unsigned budget = 23;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
