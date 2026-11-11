// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61956572;
  double density_weight = 0.03892570;
  double prefix_weight = 0.09501374;
  double neighborhood_weight = 0.12049149;
  double late_weight = 0.04461039;
  double critical_weight = 0.40996896;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
