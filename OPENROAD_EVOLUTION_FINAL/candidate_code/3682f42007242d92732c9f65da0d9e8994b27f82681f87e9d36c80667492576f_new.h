// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39555623;
  double density_weight = 0.07095207;
  double prefix_weight = 0.18537792;
  double neighborhood_weight = 0.33335217;
  double late_weight = 0.19975897;
  double critical_weight = 0.05135193;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
