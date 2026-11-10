// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77370976;
  double density_weight = 0.17959345;
  double prefix_weight = 0.44762857;
  double neighborhood_weight = 0.12795736;
  double late_weight = 0.04689719;
  double critical_weight = 0.03674173;
  unsigned budget = 25;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
