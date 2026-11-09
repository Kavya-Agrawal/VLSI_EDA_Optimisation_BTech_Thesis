// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12505438;
  double density_weight = 0.43800599;
  double prefix_weight = 0.04250572;
  double neighborhood_weight = 0.33875578;
  double late_weight = 0.21463462;
  double critical_weight = 0.20352798;
  unsigned budget = 26;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
