// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58255857;
  double density_weight = 0.00931818;
  double prefix_weight = 0.34704490;
  double neighborhood_weight = 0.15856810;
  double late_weight = 0.28521782;
  double critical_weight = 0.20569597;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
