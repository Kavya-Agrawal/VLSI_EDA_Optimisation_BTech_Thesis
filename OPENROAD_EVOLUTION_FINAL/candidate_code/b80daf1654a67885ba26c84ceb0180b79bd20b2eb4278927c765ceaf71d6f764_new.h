// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35184249;
  double density_weight = 0.19663596;
  double prefix_weight = 0.38391283;
  double neighborhood_weight = 0.09997791;
  double late_weight = 0.02987759;
  double critical_weight = 0.45938925;
  unsigned budget = 20;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
