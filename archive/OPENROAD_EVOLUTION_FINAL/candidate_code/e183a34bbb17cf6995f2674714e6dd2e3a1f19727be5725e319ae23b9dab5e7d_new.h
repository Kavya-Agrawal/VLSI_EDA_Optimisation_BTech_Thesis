// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97914655;
  double density_weight = 0.40497957;
  double prefix_weight = 0.36954961;
  double neighborhood_weight = 0.06369210;
  double late_weight = 0.04160488;
  double critical_weight = 0.07459059;
  unsigned budget = 33;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
