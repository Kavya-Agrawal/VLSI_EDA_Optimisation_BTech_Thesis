// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70002327;
  double density_weight = 0.33715326;
  double prefix_weight = 0.28248682;
  double neighborhood_weight = 0.25781513;
  double late_weight = 0.23764458;
  double critical_weight = 0.32306273;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
