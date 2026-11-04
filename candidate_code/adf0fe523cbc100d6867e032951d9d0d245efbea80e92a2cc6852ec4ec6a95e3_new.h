// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81049937;
  double density_weight = 0.47816728;
  double prefix_weight = 0.27125260;
  double neighborhood_weight = 0.26759068;
  double late_weight = 0.05884572;
  double critical_weight = 0.23921122;
  unsigned budget = 4;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
