// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12115522;
  double density_weight = 0.37515861;
  double prefix_weight = 0.22626538;
  double neighborhood_weight = 0.05337239;
  double late_weight = 0.17829839;
  double critical_weight = 0.35225622;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
