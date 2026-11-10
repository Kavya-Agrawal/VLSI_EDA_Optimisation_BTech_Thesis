// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14914382;
  double density_weight = 0.28141507;
  double prefix_weight = 0.39895684;
  double neighborhood_weight = 0.35288082;
  double late_weight = 0.22764715;
  double critical_weight = 0.47788384;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
