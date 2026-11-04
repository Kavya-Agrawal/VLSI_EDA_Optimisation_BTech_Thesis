// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47275731;
  double density_weight = 0.18097400;
  double prefix_weight = 0.14757154;
  double neighborhood_weight = 0.35112541;
  double late_weight = 0.16739240;
  double critical_weight = 0.23268797;
  unsigned budget = 34;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
