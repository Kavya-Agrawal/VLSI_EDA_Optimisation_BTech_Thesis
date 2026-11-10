// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43531011;
  double density_weight = 0.13221688;
  double prefix_weight = 0.47805095;
  double neighborhood_weight = 0.29851712;
  double late_weight = 0.26429309;
  double critical_weight = 0.09114231;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
