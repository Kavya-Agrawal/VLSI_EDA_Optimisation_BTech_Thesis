// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00783630;
  double density_weight = 0.27864595;
  double prefix_weight = 0.25187424;
  double neighborhood_weight = 0.20067047;
  double late_weight = 0.12330393;
  double critical_weight = 0.39861009;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
