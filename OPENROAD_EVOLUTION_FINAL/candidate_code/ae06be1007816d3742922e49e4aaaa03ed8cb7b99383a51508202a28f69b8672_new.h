// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60916711;
  double density_weight = 0.12373062;
  double prefix_weight = 0.29714627;
  double neighborhood_weight = 0.32985218;
  double late_weight = 0.19790190;
  double critical_weight = 0.01209797;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
