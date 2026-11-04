// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45166754;
  double density_weight = 0.51890405;
  double prefix_weight = 0.32997312;
  double neighborhood_weight = 0.19836105;
  double late_weight = 0.11938036;
  double critical_weight = 0.37789360;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
