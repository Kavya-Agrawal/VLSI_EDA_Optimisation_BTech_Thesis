// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27090846;
  double density_weight = 0.44340314;
  double prefix_weight = 0.28499663;
  double neighborhood_weight = 0.15468727;
  double late_weight = 0.02233243;
  double critical_weight = 0.22456356;
  unsigned budget = 6;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
