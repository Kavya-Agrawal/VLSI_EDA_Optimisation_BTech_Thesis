// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34166811;
  double density_weight = 0.58518777;
  double prefix_weight = 0.10949926;
  double neighborhood_weight = 0.26826202;
  double late_weight = 0.18586369;
  double critical_weight = 0.00763666;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
