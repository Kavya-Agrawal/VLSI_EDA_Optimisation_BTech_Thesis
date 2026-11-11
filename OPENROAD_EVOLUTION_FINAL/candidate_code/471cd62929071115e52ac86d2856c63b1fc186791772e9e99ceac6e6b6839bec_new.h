// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86994554;
  double density_weight = 0.24910981;
  double prefix_weight = 0.43851840;
  double neighborhood_weight = 0.31980804;
  double late_weight = 0.20625556;
  double critical_weight = 0.22611942;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
