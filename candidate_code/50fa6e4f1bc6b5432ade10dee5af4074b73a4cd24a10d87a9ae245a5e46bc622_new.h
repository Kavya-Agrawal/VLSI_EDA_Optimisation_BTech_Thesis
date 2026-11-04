// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66618864;
  double density_weight = 0.08517757;
  double prefix_weight = 0.13648555;
  double neighborhood_weight = 0.36921656;
  double late_weight = 0.03515728;
  double critical_weight = 0.26646963;
  unsigned budget = 18;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
