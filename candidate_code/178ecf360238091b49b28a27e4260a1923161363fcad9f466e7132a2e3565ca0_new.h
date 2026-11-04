// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63464163;
  double density_weight = 0.41159971;
  double prefix_weight = 0.06068298;
  double neighborhood_weight = 0.03456067;
  double late_weight = 0.07599343;
  double critical_weight = 0.17264392;
  unsigned budget = 24;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
