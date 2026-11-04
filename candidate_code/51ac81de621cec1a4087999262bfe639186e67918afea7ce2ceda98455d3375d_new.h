// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03355495;
  double density_weight = 0.27097902;
  double prefix_weight = 0.36263747;
  double neighborhood_weight = 0.07523254;
  double late_weight = 0.20254154;
  double critical_weight = 0.05751621;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
