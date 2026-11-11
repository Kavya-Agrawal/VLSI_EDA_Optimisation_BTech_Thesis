// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54453396;
  double density_weight = 0.46756525;
  double prefix_weight = 0.05627496;
  double neighborhood_weight = 0.10289224;
  double late_weight = 0.28708874;
  double critical_weight = 0.41408069;
  unsigned budget = 5;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
