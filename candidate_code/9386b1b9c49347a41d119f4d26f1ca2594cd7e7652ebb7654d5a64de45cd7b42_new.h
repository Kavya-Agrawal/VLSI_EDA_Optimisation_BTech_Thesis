// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54867701;
  double density_weight = 0.48389153;
  double prefix_weight = 0.24059247;
  double neighborhood_weight = 0.17980580;
  double late_weight = 0.05881347;
  double critical_weight = 0.47301134;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
