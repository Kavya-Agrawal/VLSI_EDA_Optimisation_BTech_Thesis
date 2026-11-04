// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77476213;
  double density_weight = 0.50301533;
  double prefix_weight = 0.33340961;
  double neighborhood_weight = 0.08259872;
  double late_weight = 0.12338518;
  double critical_weight = 0.25366813;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
