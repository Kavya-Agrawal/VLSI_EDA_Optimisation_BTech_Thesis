// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52979762;
  double density_weight = 0.47245890;
  double prefix_weight = 0.20568197;
  double neighborhood_weight = 0.27281056;
  double late_weight = 0.12043538;
  double critical_weight = 0.19089323;
  unsigned budget = 14;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
