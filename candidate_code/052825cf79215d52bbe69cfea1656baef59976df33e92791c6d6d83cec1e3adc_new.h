// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99866578;
  double density_weight = 0.54867807;
  double prefix_weight = 0.13500877;
  double neighborhood_weight = 0.11371848;
  double late_weight = 0.12014031;
  double critical_weight = 0.20086572;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
