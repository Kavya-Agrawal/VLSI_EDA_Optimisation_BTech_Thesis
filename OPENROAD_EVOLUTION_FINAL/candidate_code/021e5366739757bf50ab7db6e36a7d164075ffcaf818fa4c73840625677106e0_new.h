// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04533848;
  double density_weight = 0.18410526;
  double prefix_weight = 0.08527452;
  double neighborhood_weight = 0.22057745;
  double late_weight = 0.29351118;
  double critical_weight = 0.36669766;
  unsigned budget = 40;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
