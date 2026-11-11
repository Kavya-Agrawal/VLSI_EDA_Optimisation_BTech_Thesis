// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15210886;
  double density_weight = 0.53479824;
  double prefix_weight = 0.43478435;
  double neighborhood_weight = 0.12091851;
  double late_weight = 0.28739352;
  double critical_weight = 0.13022707;
  unsigned budget = 22;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
