// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72059114;
  double density_weight = 0.27626116;
  double prefix_weight = 0.19313092;
  double neighborhood_weight = 0.03666331;
  double late_weight = 0.15769866;
  double critical_weight = 0.32429781;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
