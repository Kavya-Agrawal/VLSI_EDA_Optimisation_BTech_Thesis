// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75760973;
  double density_weight = 0.27277461;
  double prefix_weight = 0.15787677;
  double neighborhood_weight = 0.02900355;
  double late_weight = 0.28283276;
  double critical_weight = 0.34333916;
  unsigned budget = 27;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
