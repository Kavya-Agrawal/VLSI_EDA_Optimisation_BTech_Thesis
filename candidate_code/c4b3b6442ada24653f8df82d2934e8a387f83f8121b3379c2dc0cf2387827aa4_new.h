// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61093376;
  double density_weight = 0.29939528;
  double prefix_weight = 0.42638129;
  double neighborhood_weight = 0.12388712;
  double late_weight = 0.16984036;
  double critical_weight = 0.42922054;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
