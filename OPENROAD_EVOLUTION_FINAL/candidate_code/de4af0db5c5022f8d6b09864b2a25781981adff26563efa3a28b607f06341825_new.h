// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84614606;
  double density_weight = 0.47774594;
  double prefix_weight = 0.27120468;
  double neighborhood_weight = 0.06630502;
  double late_weight = 0.06441048;
  double critical_weight = 0.12870987;
  unsigned budget = 9;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
