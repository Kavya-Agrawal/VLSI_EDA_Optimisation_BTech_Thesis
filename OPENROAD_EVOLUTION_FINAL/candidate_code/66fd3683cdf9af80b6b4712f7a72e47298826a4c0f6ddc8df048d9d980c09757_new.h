// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75628652;
  double density_weight = 0.00283462;
  double prefix_weight = 0.30434149;
  double neighborhood_weight = 0.14786527;
  double late_weight = 0.18699890;
  double critical_weight = 0.16732971;
  unsigned budget = 39;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
