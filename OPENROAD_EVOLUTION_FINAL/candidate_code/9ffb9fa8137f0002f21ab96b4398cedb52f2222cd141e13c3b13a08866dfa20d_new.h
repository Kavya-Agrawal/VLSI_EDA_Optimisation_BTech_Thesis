// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68133528;
  double density_weight = 0.39273663;
  double prefix_weight = 0.39357309;
  double neighborhood_weight = 0.01312980;
  double late_weight = 0.15837452;
  double critical_weight = 0.49325732;
  unsigned budget = 33;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
