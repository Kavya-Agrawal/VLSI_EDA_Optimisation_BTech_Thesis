// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34939594;
  double density_weight = 0.02764160;
  double prefix_weight = 0.46966993;
  double neighborhood_weight = 0.11383610;
  double late_weight = 0.02339632;
  double critical_weight = 0.14195567;
  unsigned budget = 30;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
