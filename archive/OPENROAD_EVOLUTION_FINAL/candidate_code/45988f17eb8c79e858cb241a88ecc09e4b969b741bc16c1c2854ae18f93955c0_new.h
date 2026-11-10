// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85053568;
  double density_weight = 0.45769213;
  double prefix_weight = 0.02419247;
  double neighborhood_weight = 0.39678997;
  double late_weight = 0.05578278;
  double critical_weight = 0.20537912;
  unsigned budget = 15;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
