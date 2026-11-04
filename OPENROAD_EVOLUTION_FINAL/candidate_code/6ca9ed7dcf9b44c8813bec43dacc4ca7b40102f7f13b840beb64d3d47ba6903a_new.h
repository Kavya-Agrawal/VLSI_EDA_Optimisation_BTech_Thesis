// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38092759;
  double density_weight = 0.59608844;
  double prefix_weight = 0.16625857;
  double neighborhood_weight = 0.15966584;
  double late_weight = 0.27936299;
  double critical_weight = 0.48778542;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
