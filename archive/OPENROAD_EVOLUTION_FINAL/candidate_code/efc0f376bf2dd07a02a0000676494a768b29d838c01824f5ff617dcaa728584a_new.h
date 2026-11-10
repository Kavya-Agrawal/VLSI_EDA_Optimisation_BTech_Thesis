// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32790123;
  double density_weight = 0.25152971;
  double prefix_weight = 0.47965372;
  double neighborhood_weight = 0.36172242;
  double late_weight = 0.23013939;
  double critical_weight = 0.01061901;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
