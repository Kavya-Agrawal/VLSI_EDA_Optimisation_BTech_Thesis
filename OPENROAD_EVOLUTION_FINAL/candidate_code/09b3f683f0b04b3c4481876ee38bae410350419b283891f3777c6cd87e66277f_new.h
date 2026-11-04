// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73306421;
  double density_weight = 0.07908523;
  double prefix_weight = 0.42313239;
  double neighborhood_weight = 0.18355563;
  double late_weight = 0.28809617;
  double critical_weight = 0.22255452;
  unsigned budget = 14;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
