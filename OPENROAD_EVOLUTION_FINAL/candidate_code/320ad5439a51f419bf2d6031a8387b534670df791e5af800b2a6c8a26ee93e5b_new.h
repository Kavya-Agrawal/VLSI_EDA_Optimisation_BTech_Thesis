// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71346754;
  double density_weight = 0.43227031;
  double prefix_weight = 0.09102365;
  double neighborhood_weight = 0.00464635;
  double late_weight = 0.07038226;
  double critical_weight = 0.25498393;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
