// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91119684;
  double density_weight = 0.43886454;
  double prefix_weight = 0.21561665;
  double neighborhood_weight = 0.24148870;
  double late_weight = 0.18576269;
  double critical_weight = 0.16413911;
  unsigned budget = 23;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
