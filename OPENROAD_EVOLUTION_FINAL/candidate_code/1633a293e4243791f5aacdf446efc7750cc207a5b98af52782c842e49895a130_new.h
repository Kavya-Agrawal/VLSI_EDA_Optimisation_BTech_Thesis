// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41343625;
  double density_weight = 0.53200402;
  double prefix_weight = 0.47883516;
  double neighborhood_weight = 0.20276943;
  double late_weight = 0.09224246;
  double critical_weight = 0.05626772;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
