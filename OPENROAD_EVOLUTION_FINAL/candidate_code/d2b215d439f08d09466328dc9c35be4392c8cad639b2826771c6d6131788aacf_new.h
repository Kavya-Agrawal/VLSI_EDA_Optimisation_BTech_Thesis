// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43507913;
  double density_weight = 0.37215715;
  double prefix_weight = 0.11260409;
  double neighborhood_weight = 0.07109870;
  double late_weight = 0.05215073;
  double critical_weight = 0.19941827;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
