// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63357739;
  double density_weight = 0.15477365;
  double prefix_weight = 0.10452570;
  double neighborhood_weight = 0.32724645;
  double late_weight = 0.24267954;
  double critical_weight = 0.43294591;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
