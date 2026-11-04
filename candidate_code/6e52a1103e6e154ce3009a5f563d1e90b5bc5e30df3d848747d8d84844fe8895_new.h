// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98428778;
  double density_weight = 0.43727052;
  double prefix_weight = 0.46386986;
  double neighborhood_weight = 0.10497616;
  double late_weight = 0.00904044;
  double critical_weight = 0.15517153;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
