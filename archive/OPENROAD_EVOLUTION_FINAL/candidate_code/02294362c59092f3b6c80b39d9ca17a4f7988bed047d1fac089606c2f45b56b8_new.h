// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67102097;
  double density_weight = 0.33794739;
  double prefix_weight = 0.49505409;
  double neighborhood_weight = 0.12692909;
  double late_weight = 0.01279938;
  double critical_weight = 0.24815426;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
