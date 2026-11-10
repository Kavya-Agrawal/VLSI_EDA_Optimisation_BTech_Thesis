// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31142877;
  double density_weight = 0.13944587;
  double prefix_weight = 0.31072189;
  double neighborhood_weight = 0.18616195;
  double late_weight = 0.08446572;
  double critical_weight = 0.14027777;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
