// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52138426;
  double density_weight = 0.30245125;
  double prefix_weight = 0.01891495;
  double neighborhood_weight = 0.17822878;
  double late_weight = 0.20668603;
  double critical_weight = 0.41087413;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
