// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04502090;
  double density_weight = 0.23879276;
  double prefix_weight = 0.28092960;
  double neighborhood_weight = 0.21826891;
  double late_weight = 0.07959898;
  double critical_weight = 0.03129874;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
