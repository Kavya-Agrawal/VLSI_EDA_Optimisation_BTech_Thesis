// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86894610;
  double density_weight = 0.34292740;
  double prefix_weight = 0.09563479;
  double neighborhood_weight = 0.05211032;
  double late_weight = 0.20255922;
  double critical_weight = 0.25189019;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
