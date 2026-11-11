// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91507962;
  double density_weight = 0.47073198;
  double prefix_weight = 0.49324482;
  double neighborhood_weight = 0.05409387;
  double late_weight = 0.26754385;
  double critical_weight = 0.04713497;
  unsigned budget = 16;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
