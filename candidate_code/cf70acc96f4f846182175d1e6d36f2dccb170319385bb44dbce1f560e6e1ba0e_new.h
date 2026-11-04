// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90872605;
  double density_weight = 0.15040213;
  double prefix_weight = 0.19283852;
  double neighborhood_weight = 0.22161029;
  double late_weight = 0.19782520;
  double critical_weight = 0.23313416;
  unsigned budget = 38;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
