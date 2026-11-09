// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98561826;
  double density_weight = 0.48597960;
  double prefix_weight = 0.19362727;
  double neighborhood_weight = 0.26416523;
  double late_weight = 0.03249477;
  double critical_weight = 0.49485731;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
