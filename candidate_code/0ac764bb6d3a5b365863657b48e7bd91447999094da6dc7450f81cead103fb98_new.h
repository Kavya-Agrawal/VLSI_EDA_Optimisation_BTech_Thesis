// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19196487;
  double density_weight = 0.42177938;
  double prefix_weight = 0.15458986;
  double neighborhood_weight = 0.29405572;
  double late_weight = 0.14141067;
  double critical_weight = 0.45990837;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
