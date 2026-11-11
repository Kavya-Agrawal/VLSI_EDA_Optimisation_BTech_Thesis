// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07906484;
  double density_weight = 0.05740503;
  double prefix_weight = 0.05620146;
  double neighborhood_weight = 0.29183137;
  double late_weight = 0.06458442;
  double critical_weight = 0.31923223;
  unsigned budget = 31;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
