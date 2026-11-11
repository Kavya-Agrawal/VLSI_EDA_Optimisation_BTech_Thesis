// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76090777;
  double density_weight = 0.35713805;
  double prefix_weight = 0.46348169;
  double neighborhood_weight = 0.15790023;
  double late_weight = 0.02011731;
  double critical_weight = 0.40525678;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
