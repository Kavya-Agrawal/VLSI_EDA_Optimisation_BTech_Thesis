// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48657158;
  double density_weight = 0.02274287;
  double prefix_weight = 0.49488148;
  double neighborhood_weight = 0.31935885;
  double late_weight = 0.00410338;
  double critical_weight = 0.35582206;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
