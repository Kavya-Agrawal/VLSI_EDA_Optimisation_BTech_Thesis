// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74287999;
  double density_weight = 0.56311623;
  double prefix_weight = 0.00979446;
  double neighborhood_weight = 0.22898375;
  double late_weight = 0.20313399;
  double critical_weight = 0.36028498;
  unsigned budget = 18;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
