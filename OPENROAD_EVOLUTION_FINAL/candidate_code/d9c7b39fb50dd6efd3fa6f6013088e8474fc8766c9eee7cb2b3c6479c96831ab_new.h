// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63245577;
  double density_weight = 0.31770823;
  double prefix_weight = 0.26811165;
  double neighborhood_weight = 0.37086381;
  double late_weight = 0.08391940;
  double critical_weight = 0.24548830;
  unsigned budget = 8;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
