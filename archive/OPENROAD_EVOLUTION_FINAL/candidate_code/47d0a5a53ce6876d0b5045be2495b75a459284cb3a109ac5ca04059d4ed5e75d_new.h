// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62500557;
  double density_weight = 0.41263718;
  double prefix_weight = 0.05837771;
  double neighborhood_weight = 0.39746825;
  double late_weight = 0.13508985;
  double critical_weight = 0.46952385;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
