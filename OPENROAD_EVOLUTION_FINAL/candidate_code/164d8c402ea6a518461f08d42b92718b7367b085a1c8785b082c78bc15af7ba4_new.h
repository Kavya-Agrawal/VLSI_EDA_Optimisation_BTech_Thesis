// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52378338;
  double density_weight = 0.47557122;
  double prefix_weight = 0.00615665;
  double neighborhood_weight = 0.36591573;
  double late_weight = 0.09101104;
  double critical_weight = 0.26601936;
  unsigned budget = 10;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
