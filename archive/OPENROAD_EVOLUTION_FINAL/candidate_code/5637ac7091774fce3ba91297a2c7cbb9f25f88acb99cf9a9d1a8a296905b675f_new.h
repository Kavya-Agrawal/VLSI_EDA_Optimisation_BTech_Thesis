// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24222753;
  double density_weight = 0.17443852;
  double prefix_weight = 0.23229424;
  double neighborhood_weight = 0.07407743;
  double late_weight = 0.27240535;
  double critical_weight = 0.16087180;
  unsigned budget = 25;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
