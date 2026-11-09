// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09114022;
  double density_weight = 0.07532946;
  double prefix_weight = 0.11267836;
  double neighborhood_weight = 0.10947141;
  double late_weight = 0.26142087;
  double critical_weight = 0.47606402;
  unsigned budget = 29;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
