// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03208449;
  double density_weight = 0.56317310;
  double prefix_weight = 0.16266641;
  double neighborhood_weight = 0.32886067;
  double late_weight = 0.17333010;
  double critical_weight = 0.46454337;
  unsigned budget = 18;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
