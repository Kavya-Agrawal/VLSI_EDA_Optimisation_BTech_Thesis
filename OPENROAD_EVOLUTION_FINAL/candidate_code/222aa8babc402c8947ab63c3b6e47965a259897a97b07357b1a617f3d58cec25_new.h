// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47971856;
  double density_weight = 0.37221415;
  double prefix_weight = 0.21078677;
  double neighborhood_weight = 0.18452387;
  double late_weight = 0.23887277;
  double critical_weight = 0.19004101;
  unsigned budget = 29;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
