// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21316572;
  double density_weight = 0.24606799;
  double prefix_weight = 0.21613420;
  double neighborhood_weight = 0.39547154;
  double late_weight = 0.16457234;
  double critical_weight = 0.35463485;
  unsigned budget = 9;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
