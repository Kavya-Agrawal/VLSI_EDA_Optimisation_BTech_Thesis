// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22342405;
  double density_weight = 0.33785809;
  double prefix_weight = 0.00938238;
  double neighborhood_weight = 0.20624272;
  double late_weight = 0.17575938;
  double critical_weight = 0.15073055;
  unsigned budget = 5;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
