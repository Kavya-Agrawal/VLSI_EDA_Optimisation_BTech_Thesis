// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80465987;
  double density_weight = 0.25324100;
  double prefix_weight = 0.45568051;
  double neighborhood_weight = 0.38727197;
  double late_weight = 0.07473115;
  double critical_weight = 0.10824387;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
