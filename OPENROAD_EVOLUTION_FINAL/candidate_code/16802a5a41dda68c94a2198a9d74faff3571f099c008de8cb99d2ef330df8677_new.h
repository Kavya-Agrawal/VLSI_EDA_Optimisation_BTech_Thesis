// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25689228;
  double density_weight = 0.23245130;
  double prefix_weight = 0.05208967;
  double neighborhood_weight = 0.19236589;
  double late_weight = 0.16346246;
  double critical_weight = 0.01342064;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
