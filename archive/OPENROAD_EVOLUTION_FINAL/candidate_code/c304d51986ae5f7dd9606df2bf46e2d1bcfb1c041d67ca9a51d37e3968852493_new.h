// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28582329;
  double density_weight = 0.22501036;
  double prefix_weight = 0.21591610;
  double neighborhood_weight = 0.19177285;
  double late_weight = 0.09897760;
  double critical_weight = 0.19403684;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
