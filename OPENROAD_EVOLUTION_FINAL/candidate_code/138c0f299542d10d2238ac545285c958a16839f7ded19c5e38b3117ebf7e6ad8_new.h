// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54622180;
  double density_weight = 0.18608506;
  double prefix_weight = 0.47355609;
  double neighborhood_weight = 0.23174426;
  double late_weight = 0.24784028;
  double critical_weight = 0.22815350;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
