// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67871182;
  double density_weight = 0.58443272;
  double prefix_weight = 0.24417825;
  double neighborhood_weight = 0.04900858;
  double late_weight = 0.08599420;
  double critical_weight = 0.13768642;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
