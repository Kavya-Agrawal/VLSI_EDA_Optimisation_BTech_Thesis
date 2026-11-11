// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79715905;
  double density_weight = 0.32192223;
  double prefix_weight = 0.09295077;
  double neighborhood_weight = 0.31791811;
  double late_weight = 0.19648040;
  double critical_weight = 0.38610837;
  unsigned budget = 17;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
