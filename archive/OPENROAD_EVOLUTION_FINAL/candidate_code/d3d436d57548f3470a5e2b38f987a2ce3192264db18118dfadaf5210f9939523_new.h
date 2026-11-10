// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77926178;
  double density_weight = 0.49876591;
  double prefix_weight = 0.37220349;
  double neighborhood_weight = 0.02361038;
  double late_weight = 0.13456525;
  double critical_weight = 0.14591452;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
