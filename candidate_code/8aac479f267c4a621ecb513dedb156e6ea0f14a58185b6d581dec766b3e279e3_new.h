// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95785309;
  double density_weight = 0.02233402;
  double prefix_weight = 0.09038621;
  double neighborhood_weight = 0.37744976;
  double late_weight = 0.25329230;
  double critical_weight = 0.25801560;
  unsigned budget = 30;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
