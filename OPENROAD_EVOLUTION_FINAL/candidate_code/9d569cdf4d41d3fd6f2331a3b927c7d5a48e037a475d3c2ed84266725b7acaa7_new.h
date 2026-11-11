// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82536647;
  double density_weight = 0.40795568;
  double prefix_weight = 0.20481163;
  double neighborhood_weight = 0.19422076;
  double late_weight = 0.24853590;
  double critical_weight = 0.48453523;
  unsigned budget = 35;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
