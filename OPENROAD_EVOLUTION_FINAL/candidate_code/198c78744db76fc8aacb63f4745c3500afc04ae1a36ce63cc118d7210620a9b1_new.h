// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97250397;
  double density_weight = 0.45890540;
  double prefix_weight = 0.46923756;
  double neighborhood_weight = 0.36554152;
  double late_weight = 0.01228444;
  double critical_weight = 0.06086131;
  unsigned budget = 27;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
