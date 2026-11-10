// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32393390;
  double density_weight = 0.21883122;
  double prefix_weight = 0.33703434;
  double neighborhood_weight = 0.07040575;
  double late_weight = 0.08500762;
  double critical_weight = 0.24146177;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
