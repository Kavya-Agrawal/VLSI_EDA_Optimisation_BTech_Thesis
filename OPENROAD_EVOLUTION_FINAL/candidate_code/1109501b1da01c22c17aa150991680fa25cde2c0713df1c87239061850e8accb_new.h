// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31170219;
  double density_weight = 0.15244107;
  double prefix_weight = 0.39093279;
  double neighborhood_weight = 0.28234042;
  double late_weight = 0.01472808;
  double critical_weight = 0.13019625;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
