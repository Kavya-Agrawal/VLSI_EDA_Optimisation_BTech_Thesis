// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21643503;
  double density_weight = 0.21200420;
  double prefix_weight = 0.22639179;
  double neighborhood_weight = 0.21164194;
  double late_weight = 0.22606160;
  double critical_weight = 0.27401094;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
