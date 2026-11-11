// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69969133;
  double density_weight = 0.39944817;
  double prefix_weight = 0.12776358;
  double neighborhood_weight = 0.34257918;
  double late_weight = 0.17882894;
  double critical_weight = 0.23612234;
  unsigned budget = 25;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
