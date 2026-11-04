// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61302812;
  double density_weight = 0.55431332;
  double prefix_weight = 0.05555478;
  double neighborhood_weight = 0.21072933;
  double late_weight = 0.21369571;
  double critical_weight = 0.13911271;
  unsigned budget = 24;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
