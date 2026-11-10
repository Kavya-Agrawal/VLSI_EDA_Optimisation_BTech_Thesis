// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74306286;
  double density_weight = 0.22908452;
  double prefix_weight = 0.13966259;
  double neighborhood_weight = 0.30759620;
  double late_weight = 0.25734817;
  double critical_weight = 0.48326352;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
