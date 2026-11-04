// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83043314;
  double density_weight = 0.25265914;
  double prefix_weight = 0.22615129;
  double neighborhood_weight = 0.21230158;
  double late_weight = 0.29527801;
  double critical_weight = 0.15270238;
  unsigned budget = 19;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
