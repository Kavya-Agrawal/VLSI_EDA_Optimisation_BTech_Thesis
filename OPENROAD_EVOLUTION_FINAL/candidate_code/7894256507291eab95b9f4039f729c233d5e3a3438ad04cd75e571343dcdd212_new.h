// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98594192;
  double density_weight = 0.20664185;
  double prefix_weight = 0.43096141;
  double neighborhood_weight = 0.15942695;
  double late_weight = 0.13682166;
  double critical_weight = 0.45569204;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
