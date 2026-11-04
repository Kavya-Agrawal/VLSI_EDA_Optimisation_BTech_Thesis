// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04950469;
  double density_weight = 0.24121488;
  double prefix_weight = 0.36161214;
  double neighborhood_weight = 0.16732972;
  double late_weight = 0.24280206;
  double critical_weight = 0.15595415;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
