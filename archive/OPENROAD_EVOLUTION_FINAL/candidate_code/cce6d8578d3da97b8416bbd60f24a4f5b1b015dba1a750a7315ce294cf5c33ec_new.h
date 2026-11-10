// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22233940;
  double density_weight = 0.20760875;
  double prefix_weight = 0.34748753;
  double neighborhood_weight = 0.28492565;
  double late_weight = 0.10719452;
  double critical_weight = 0.07176235;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
