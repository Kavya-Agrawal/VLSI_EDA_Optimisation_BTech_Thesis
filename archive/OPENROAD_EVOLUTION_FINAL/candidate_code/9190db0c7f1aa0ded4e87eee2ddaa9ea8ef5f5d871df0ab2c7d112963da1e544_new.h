// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35334073;
  double density_weight = 0.33627625;
  double prefix_weight = 0.24289014;
  double neighborhood_weight = 0.33320250;
  double late_weight = 0.11266300;
  double critical_weight = 0.00242255;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
