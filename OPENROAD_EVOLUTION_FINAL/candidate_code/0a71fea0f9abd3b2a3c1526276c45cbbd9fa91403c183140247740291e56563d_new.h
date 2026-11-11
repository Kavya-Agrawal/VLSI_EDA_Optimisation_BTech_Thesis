// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25996419;
  double density_weight = 0.14431725;
  double prefix_weight = 0.17758965;
  double neighborhood_weight = 0.14997032;
  double late_weight = 0.03240267;
  double critical_weight = 0.32113931;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
