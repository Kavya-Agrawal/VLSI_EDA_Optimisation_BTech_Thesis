// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75434107;
  double density_weight = 0.13741499;
  double prefix_weight = 0.10844729;
  double neighborhood_weight = 0.21756684;
  double late_weight = 0.28981158;
  double critical_weight = 0.09544213;
  unsigned budget = 5;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
