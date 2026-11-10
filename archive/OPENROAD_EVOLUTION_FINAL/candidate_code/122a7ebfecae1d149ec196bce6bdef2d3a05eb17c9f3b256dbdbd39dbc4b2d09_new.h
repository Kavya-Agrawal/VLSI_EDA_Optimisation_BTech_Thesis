// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83894100;
  double density_weight = 0.30065797;
  double prefix_weight = 0.07141434;
  double neighborhood_weight = 0.31194472;
  double late_weight = 0.13392679;
  double critical_weight = 0.07802874;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
