// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39007825;
  double density_weight = 0.21381130;
  double prefix_weight = 0.04925684;
  double neighborhood_weight = 0.02538215;
  double late_weight = 0.25704414;
  double critical_weight = 0.00780590;
  unsigned budget = 8;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
