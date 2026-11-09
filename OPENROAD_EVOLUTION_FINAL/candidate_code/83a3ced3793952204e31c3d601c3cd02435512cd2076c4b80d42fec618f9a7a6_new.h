// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66167088;
  double density_weight = 0.39472943;
  double prefix_weight = 0.05551717;
  double neighborhood_weight = 0.03827917;
  double late_weight = 0.17379504;
  double critical_weight = 0.04961460;
  unsigned budget = 35;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
