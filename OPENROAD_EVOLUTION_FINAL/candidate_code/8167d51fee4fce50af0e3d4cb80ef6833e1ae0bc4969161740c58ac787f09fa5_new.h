// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04702396;
  double density_weight = 0.51197213;
  double prefix_weight = 0.11211182;
  double neighborhood_weight = 0.28823992;
  double late_weight = 0.16624346;
  double critical_weight = 0.45653489;
  unsigned budget = 5;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
