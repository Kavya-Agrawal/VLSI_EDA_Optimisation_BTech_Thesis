// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88322001;
  double density_weight = 0.10882146;
  double prefix_weight = 0.40729831;
  double neighborhood_weight = 0.37251026;
  double late_weight = 0.25433705;
  double critical_weight = 0.43768766;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
