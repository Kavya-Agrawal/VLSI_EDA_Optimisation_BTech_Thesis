// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72446363;
  double density_weight = 0.48539335;
  double prefix_weight = 0.00906834;
  double neighborhood_weight = 0.38403399;
  double late_weight = 0.13147291;
  double critical_weight = 0.00647026;
  unsigned budget = 6;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
