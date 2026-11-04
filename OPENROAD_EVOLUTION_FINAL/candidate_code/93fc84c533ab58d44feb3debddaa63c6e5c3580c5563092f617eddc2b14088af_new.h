// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83890117;
  double density_weight = 0.51554979;
  double prefix_weight = 0.20673321;
  double neighborhood_weight = 0.31900154;
  double late_weight = 0.21596947;
  double critical_weight = 0.43086729;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
