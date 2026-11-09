// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57225938;
  double density_weight = 0.01799632;
  double prefix_weight = 0.13537194;
  double neighborhood_weight = 0.03338130;
  double late_weight = 0.25603022;
  double critical_weight = 0.29227681;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
