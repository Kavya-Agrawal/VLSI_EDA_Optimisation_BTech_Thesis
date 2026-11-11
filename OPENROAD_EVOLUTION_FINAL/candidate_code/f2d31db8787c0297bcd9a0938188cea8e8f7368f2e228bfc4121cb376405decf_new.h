// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47733174;
  double density_weight = 0.53603420;
  double prefix_weight = 0.25581661;
  double neighborhood_weight = 0.02642484;
  double late_weight = 0.11655470;
  double critical_weight = 0.16544339;
  unsigned budget = 23;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
