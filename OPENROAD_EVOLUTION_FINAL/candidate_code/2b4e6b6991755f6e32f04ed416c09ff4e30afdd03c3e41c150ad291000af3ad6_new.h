// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01835625;
  double density_weight = 0.16631918;
  double prefix_weight = 0.09046129;
  double neighborhood_weight = 0.26445323;
  double late_weight = 0.05430332;
  double critical_weight = 0.16718595;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
