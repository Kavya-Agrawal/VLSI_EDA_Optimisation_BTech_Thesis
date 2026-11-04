// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51739278;
  double density_weight = 0.54016231;
  double prefix_weight = 0.43471415;
  double neighborhood_weight = 0.15016035;
  double late_weight = 0.04383242;
  double critical_weight = 0.04153223;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
