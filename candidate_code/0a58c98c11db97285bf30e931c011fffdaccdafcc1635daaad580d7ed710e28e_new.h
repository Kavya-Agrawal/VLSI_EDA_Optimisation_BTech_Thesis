// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20187416;
  double density_weight = 0.53187450;
  double prefix_weight = 0.05661991;
  double neighborhood_weight = 0.26134857;
  double late_weight = 0.18049029;
  double critical_weight = 0.12072096;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
