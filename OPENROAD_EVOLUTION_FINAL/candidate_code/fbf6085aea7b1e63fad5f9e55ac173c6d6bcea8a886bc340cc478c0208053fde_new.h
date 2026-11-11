// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68068577;
  double density_weight = 0.12344131;
  double prefix_weight = 0.07688278;
  double neighborhood_weight = 0.29782516;
  double late_weight = 0.15028367;
  double critical_weight = 0.38946078;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
