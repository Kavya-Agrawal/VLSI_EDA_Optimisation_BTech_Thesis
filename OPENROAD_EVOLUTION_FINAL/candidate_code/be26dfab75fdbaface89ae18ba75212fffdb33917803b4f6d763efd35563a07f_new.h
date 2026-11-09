// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55697834;
  double density_weight = 0.35411412;
  double prefix_weight = 0.33493740;
  double neighborhood_weight = 0.02623981;
  double late_weight = 0.26977349;
  double critical_weight = 0.46952739;
  unsigned budget = 22;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
