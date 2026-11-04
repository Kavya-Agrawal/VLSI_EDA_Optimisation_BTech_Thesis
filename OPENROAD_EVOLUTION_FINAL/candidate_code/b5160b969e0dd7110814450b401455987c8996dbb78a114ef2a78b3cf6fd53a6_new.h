// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72152489;
  double density_weight = 0.12372965;
  double prefix_weight = 0.19581822;
  double neighborhood_weight = 0.01130962;
  double late_weight = 0.25002244;
  double critical_weight = 0.26013359;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
