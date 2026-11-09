// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73269807;
  double density_weight = 0.10174598;
  double prefix_weight = 0.20906604;
  double neighborhood_weight = 0.17970603;
  double late_weight = 0.09447064;
  double critical_weight = 0.18210276;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
