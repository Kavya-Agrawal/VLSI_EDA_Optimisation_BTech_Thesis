// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61828694;
  double density_weight = 0.21152338;
  double prefix_weight = 0.38332262;
  double neighborhood_weight = 0.08530332;
  double late_weight = 0.14824507;
  double critical_weight = 0.35616359;
  unsigned budget = 30;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
