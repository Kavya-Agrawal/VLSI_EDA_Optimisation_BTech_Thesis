// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20845625;
  double density_weight = 0.12312354;
  double prefix_weight = 0.24127152;
  double neighborhood_weight = 0.06671014;
  double late_weight = 0.15278025;
  double critical_weight = 0.01849758;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
