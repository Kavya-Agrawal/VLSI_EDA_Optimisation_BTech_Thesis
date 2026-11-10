// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68217046;
  double density_weight = 0.42600041;
  double prefix_weight = 0.04562067;
  double neighborhood_weight = 0.10094127;
  double late_weight = 0.17444615;
  double critical_weight = 0.26445611;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
