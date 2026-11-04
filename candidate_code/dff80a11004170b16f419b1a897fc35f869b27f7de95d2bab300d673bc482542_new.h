// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58425574;
  double density_weight = 0.15688575;
  double prefix_weight = 0.14664431;
  double neighborhood_weight = 0.29482570;
  double late_weight = 0.27228280;
  double critical_weight = 0.35898204;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
