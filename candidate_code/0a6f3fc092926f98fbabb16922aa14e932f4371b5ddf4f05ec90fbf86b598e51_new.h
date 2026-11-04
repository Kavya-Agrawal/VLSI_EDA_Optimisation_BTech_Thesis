// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68316989;
  double density_weight = 0.14549940;
  double prefix_weight = 0.20894407;
  double neighborhood_weight = 0.08150590;
  double late_weight = 0.08365593;
  double critical_weight = 0.39518870;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
