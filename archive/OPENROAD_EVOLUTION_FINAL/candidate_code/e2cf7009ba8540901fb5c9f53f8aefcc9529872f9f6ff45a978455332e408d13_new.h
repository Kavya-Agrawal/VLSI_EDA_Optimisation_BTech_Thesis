// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61093418;
  double density_weight = 0.00132902;
  double prefix_weight = 0.04573120;
  double neighborhood_weight = 0.31227604;
  double late_weight = 0.23005368;
  double critical_weight = 0.01281342;
  unsigned budget = 13;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
