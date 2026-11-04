// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52169850;
  double density_weight = 0.53400104;
  double prefix_weight = 0.13955712;
  double neighborhood_weight = 0.22069211;
  double late_weight = 0.13258337;
  double critical_weight = 0.48623218;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
