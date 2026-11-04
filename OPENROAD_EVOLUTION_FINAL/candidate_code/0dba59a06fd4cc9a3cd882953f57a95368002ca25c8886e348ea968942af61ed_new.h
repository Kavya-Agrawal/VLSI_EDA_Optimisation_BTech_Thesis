// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71051343;
  double density_weight = 0.28220131;
  double prefix_weight = 0.01773469;
  double neighborhood_weight = 0.34477750;
  double late_weight = 0.07985437;
  double critical_weight = 0.43049886;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
