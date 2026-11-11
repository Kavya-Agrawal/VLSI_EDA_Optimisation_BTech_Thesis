// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05603301;
  double density_weight = 0.57891360;
  double prefix_weight = 0.29113207;
  double neighborhood_weight = 0.08464911;
  double late_weight = 0.04509952;
  double critical_weight = 0.23301200;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
