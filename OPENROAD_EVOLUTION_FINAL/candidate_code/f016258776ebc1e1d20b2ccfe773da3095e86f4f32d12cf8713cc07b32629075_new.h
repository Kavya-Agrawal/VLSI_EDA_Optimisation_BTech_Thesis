// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92480787;
  double density_weight = 0.13996476;
  double prefix_weight = 0.49202421;
  double neighborhood_weight = 0.20815687;
  double late_weight = 0.12766731;
  double critical_weight = 0.47900454;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
