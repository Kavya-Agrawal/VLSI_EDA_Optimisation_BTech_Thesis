// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51648898;
  double density_weight = 0.20748633;
  double prefix_weight = 0.17251790;
  double neighborhood_weight = 0.07872328;
  double late_weight = 0.05641731;
  double critical_weight = 0.03694691;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
