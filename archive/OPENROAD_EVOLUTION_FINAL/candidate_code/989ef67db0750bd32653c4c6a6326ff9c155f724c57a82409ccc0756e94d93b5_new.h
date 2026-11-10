// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73454717;
  double density_weight = 0.10206218;
  double prefix_weight = 0.24208405;
  double neighborhood_weight = 0.15212873;
  double late_weight = 0.06370281;
  double critical_weight = 0.36116858;
  unsigned budget = 36;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
