// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98292983;
  double density_weight = 0.58474354;
  double prefix_weight = 0.14414094;
  double neighborhood_weight = 0.01442031;
  double late_weight = 0.20476250;
  double critical_weight = 0.21889039;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
