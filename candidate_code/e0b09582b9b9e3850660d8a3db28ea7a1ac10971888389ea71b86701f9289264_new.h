// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89544217;
  double density_weight = 0.45114102;
  double prefix_weight = 0.15591304;
  double neighborhood_weight = 0.07387333;
  double late_weight = 0.21488271;
  double critical_weight = 0.22356531;
  unsigned budget = 27;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
