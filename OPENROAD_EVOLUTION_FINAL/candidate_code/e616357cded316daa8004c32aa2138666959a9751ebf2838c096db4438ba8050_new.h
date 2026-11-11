// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48560157;
  double density_weight = 0.11428032;
  double prefix_weight = 0.23265847;
  double neighborhood_weight = 0.38325056;
  double late_weight = 0.25898065;
  double critical_weight = 0.34019526;
  unsigned budget = 28;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
