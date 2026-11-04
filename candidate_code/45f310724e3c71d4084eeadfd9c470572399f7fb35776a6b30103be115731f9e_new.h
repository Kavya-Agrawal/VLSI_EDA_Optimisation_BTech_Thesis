// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02167305;
  double density_weight = 0.58381906;
  double prefix_weight = 0.30603332;
  double neighborhood_weight = 0.18829716;
  double late_weight = 0.17897336;
  double critical_weight = 0.22933927;
  unsigned budget = 8;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
