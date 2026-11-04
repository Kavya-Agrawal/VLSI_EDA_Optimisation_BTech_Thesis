// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37729360;
  double density_weight = 0.31822207;
  double prefix_weight = 0.47296065;
  double neighborhood_weight = 0.39363719;
  double late_weight = 0.07147696;
  double critical_weight = 0.03405184;
  unsigned budget = 24;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
