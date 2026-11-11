// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51676192;
  double density_weight = 0.57606397;
  double prefix_weight = 0.31005126;
  double neighborhood_weight = 0.05796071;
  double late_weight = 0.19613681;
  double critical_weight = 0.33964707;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
