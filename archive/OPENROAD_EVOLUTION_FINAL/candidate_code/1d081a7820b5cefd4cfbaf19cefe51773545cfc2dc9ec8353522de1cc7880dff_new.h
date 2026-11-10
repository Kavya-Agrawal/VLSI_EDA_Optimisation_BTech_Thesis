// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15477098;
  double density_weight = 0.29188135;
  double prefix_weight = 0.42925504;
  double neighborhood_weight = 0.21230584;
  double late_weight = 0.27032744;
  double critical_weight = 0.00981069;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
