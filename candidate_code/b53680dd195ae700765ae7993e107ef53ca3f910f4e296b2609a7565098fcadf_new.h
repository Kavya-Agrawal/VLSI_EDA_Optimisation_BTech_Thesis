// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61596552;
  double density_weight = 0.58408254;
  double prefix_weight = 0.07511039;
  double neighborhood_weight = 0.21078308;
  double late_weight = 0.09613458;
  double critical_weight = 0.03198950;
  unsigned budget = 39;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
