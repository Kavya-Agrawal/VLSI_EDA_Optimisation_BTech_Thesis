// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72591926;
  double density_weight = 0.12598980;
  double prefix_weight = 0.40082452;
  double neighborhood_weight = 0.03171902;
  double late_weight = 0.24871529;
  double critical_weight = 0.28793931;
  unsigned budget = 35;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
