// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54009552;
  double density_weight = 0.00205758;
  double prefix_weight = 0.08622376;
  double neighborhood_weight = 0.26689764;
  double late_weight = 0.13663811;
  double critical_weight = 0.24864959;
  unsigned budget = 26;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
