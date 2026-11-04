// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47403166;
  double density_weight = 0.39228421;
  double prefix_weight = 0.47428582;
  double neighborhood_weight = 0.34511751;
  double late_weight = 0.25102368;
  double critical_weight = 0.14613587;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
