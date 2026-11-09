// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12786330;
  double density_weight = 0.46251909;
  double prefix_weight = 0.13882206;
  double neighborhood_weight = 0.15968611;
  double late_weight = 0.29202195;
  double critical_weight = 0.28429973;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
