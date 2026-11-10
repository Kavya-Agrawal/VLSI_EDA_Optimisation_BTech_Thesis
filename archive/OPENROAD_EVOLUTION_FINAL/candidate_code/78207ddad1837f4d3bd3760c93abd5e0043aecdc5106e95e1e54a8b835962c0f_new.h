// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46294301;
  double density_weight = 0.01916572;
  double prefix_weight = 0.06612561;
  double neighborhood_weight = 0.26148772;
  double late_weight = 0.21806355;
  double critical_weight = 0.07427255;
  unsigned budget = 38;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
