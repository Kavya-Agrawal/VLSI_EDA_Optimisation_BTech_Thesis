// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17648401;
  double density_weight = 0.21769050;
  double prefix_weight = 0.44525396;
  double neighborhood_weight = 0.29979533;
  double late_weight = 0.27675864;
  double critical_weight = 0.30436858;
  unsigned budget = 8;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
