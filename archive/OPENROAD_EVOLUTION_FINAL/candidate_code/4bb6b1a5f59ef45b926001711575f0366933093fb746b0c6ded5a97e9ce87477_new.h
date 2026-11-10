// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96554938;
  double density_weight = 0.59350101;
  double prefix_weight = 0.08084739;
  double neighborhood_weight = 0.14862546;
  double late_weight = 0.10812358;
  double critical_weight = 0.09535466;
  unsigned budget = 29;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
