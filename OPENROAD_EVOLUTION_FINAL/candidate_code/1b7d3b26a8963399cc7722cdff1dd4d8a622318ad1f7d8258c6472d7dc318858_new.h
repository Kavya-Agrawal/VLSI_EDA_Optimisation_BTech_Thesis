// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66945795;
  double density_weight = 0.42523181;
  double prefix_weight = 0.24132041;
  double neighborhood_weight = 0.01454287;
  double late_weight = 0.11456518;
  double critical_weight = 0.39374616;
  unsigned budget = 25;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
