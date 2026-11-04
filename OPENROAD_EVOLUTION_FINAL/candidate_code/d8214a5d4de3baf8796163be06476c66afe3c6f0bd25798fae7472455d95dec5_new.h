// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92606689;
  double density_weight = 0.51026197;
  double prefix_weight = 0.21462303;
  double neighborhood_weight = 0.06744753;
  double late_weight = 0.06103953;
  double critical_weight = 0.28068278;
  unsigned budget = 6;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
