// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89580942;
  double density_weight = 0.53196894;
  double prefix_weight = 0.06850154;
  double neighborhood_weight = 0.38229226;
  double late_weight = 0.20846979;
  double critical_weight = 0.35550601;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
