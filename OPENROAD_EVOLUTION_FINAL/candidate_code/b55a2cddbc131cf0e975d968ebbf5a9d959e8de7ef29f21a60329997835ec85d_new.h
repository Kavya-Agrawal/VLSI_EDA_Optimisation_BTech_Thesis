// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21155865;
  double density_weight = 0.19035783;
  double prefix_weight = 0.47455055;
  double neighborhood_weight = 0.09484254;
  double late_weight = 0.05379067;
  double critical_weight = 0.05014055;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
