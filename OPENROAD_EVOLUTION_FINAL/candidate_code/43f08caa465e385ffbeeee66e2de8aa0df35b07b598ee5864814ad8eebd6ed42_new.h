// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87886290;
  double density_weight = 0.58806208;
  double prefix_weight = 0.36745571;
  double neighborhood_weight = 0.06138228;
  double late_weight = 0.18362303;
  double critical_weight = 0.29451100;
  unsigned budget = 15;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
