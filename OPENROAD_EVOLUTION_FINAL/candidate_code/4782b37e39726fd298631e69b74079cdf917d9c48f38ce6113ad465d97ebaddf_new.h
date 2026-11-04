// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55953070;
  double density_weight = 0.09824913;
  double prefix_weight = 0.41646246;
  double neighborhood_weight = 0.25231702;
  double late_weight = 0.17156097;
  double critical_weight = 0.01502772;
  unsigned budget = 40;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
