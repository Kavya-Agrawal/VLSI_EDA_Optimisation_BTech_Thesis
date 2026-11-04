// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92811691;
  double density_weight = 0.21048639;
  double prefix_weight = 0.31559924;
  double neighborhood_weight = 0.39572522;
  double late_weight = 0.15916506;
  double critical_weight = 0.17201939;
  unsigned budget = 15;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
