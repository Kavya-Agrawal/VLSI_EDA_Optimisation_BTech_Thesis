// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50609535;
  double density_weight = 0.16673265;
  double prefix_weight = 0.03628354;
  double neighborhood_weight = 0.21997515;
  double late_weight = 0.12328134;
  double critical_weight = 0.40866256;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
