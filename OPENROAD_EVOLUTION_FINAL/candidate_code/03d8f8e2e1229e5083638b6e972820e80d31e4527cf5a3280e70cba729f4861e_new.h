// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62148823;
  double density_weight = 0.56520335;
  double prefix_weight = 0.19380780;
  double neighborhood_weight = 0.16973069;
  double late_weight = 0.15850094;
  double critical_weight = 0.19063744;
  unsigned budget = 35;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
