// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00679601;
  double density_weight = 0.17413979;
  double prefix_weight = 0.05661122;
  double neighborhood_weight = 0.27594295;
  double late_weight = 0.01484969;
  double critical_weight = 0.19879561;
  unsigned budget = 5;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
