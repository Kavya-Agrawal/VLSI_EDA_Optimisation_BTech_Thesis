// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36161252;
  double density_weight = 0.36834055;
  double prefix_weight = 0.48317320;
  double neighborhood_weight = 0.15948336;
  double late_weight = 0.16417653;
  double critical_weight = 0.01082980;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
