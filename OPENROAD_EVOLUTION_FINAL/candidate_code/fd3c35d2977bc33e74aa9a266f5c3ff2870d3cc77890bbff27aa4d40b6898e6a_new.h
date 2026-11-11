// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30230358;
  double density_weight = 0.46846401;
  double prefix_weight = 0.42553826;
  double neighborhood_weight = 0.19378406;
  double late_weight = 0.10021794;
  double critical_weight = 0.02260396;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
