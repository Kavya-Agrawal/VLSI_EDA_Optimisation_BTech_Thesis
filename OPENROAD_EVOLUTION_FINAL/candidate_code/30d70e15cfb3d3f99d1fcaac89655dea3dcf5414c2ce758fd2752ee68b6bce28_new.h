// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31409154;
  double density_weight = 0.17617476;
  double prefix_weight = 0.34076364;
  double neighborhood_weight = 0.25269561;
  double late_weight = 0.13226299;
  double critical_weight = 0.15900042;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
