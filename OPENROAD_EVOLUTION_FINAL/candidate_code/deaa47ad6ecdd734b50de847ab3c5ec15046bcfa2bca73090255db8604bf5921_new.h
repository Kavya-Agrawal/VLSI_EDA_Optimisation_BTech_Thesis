// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69264271;
  double density_weight = 0.27106786;
  double prefix_weight = 0.16834482;
  double neighborhood_weight = 0.39817261;
  double late_weight = 0.18057854;
  double critical_weight = 0.33220837;
  unsigned budget = 14;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
