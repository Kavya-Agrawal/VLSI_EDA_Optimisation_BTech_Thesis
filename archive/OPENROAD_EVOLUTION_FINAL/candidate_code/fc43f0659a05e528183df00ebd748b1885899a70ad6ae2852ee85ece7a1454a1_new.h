// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27191992;
  double density_weight = 0.20265909;
  double prefix_weight = 0.02158716;
  double neighborhood_weight = 0.08781332;
  double late_weight = 0.25113072;
  double critical_weight = 0.34750340;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
