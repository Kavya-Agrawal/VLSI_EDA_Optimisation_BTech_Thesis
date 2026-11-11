// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40024945;
  double density_weight = 0.38336233;
  double prefix_weight = 0.06886067;
  double neighborhood_weight = 0.02018657;
  double late_weight = 0.13985007;
  double critical_weight = 0.26009064;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
