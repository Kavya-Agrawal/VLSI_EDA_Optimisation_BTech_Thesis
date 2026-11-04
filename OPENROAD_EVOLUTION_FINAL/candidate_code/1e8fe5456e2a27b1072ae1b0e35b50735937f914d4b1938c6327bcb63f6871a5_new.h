// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47438085;
  double density_weight = 0.02969295;
  double prefix_weight = 0.43180542;
  double neighborhood_weight = 0.02935379;
  double late_weight = 0.01077157;
  double critical_weight = 0.17100296;
  unsigned budget = 38;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
