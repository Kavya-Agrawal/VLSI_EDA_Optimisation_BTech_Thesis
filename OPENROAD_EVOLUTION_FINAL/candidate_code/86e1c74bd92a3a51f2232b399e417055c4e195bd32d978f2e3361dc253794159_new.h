// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62384535;
  double density_weight = 0.41876355;
  double prefix_weight = 0.24226157;
  double neighborhood_weight = 0.37973086;
  double late_weight = 0.23878802;
  double critical_weight = 0.33623198;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
