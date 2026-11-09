// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98400849;
  double density_weight = 0.08479918;
  double prefix_weight = 0.15429363;
  double neighborhood_weight = 0.36557309;
  double late_weight = 0.12762924;
  double critical_weight = 0.33369926;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
