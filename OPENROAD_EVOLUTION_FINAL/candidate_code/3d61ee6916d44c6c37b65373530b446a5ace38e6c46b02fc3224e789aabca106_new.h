// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07343621;
  double density_weight = 0.49296740;
  double prefix_weight = 0.05484431;
  double neighborhood_weight = 0.19655071;
  double late_weight = 0.03057929;
  double critical_weight = 0.09545267;
  unsigned budget = 10;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
