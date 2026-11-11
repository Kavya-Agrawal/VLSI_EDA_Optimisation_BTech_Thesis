// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95075288;
  double density_weight = 0.04120694;
  double prefix_weight = 0.43831802;
  double neighborhood_weight = 0.34156447;
  double late_weight = 0.10623309;
  double critical_weight = 0.37098182;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
