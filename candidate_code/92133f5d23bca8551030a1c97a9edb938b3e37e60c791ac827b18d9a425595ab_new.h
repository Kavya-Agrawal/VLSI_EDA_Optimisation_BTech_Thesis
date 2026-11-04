// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79733475;
  double density_weight = 0.28252541;
  double prefix_weight = 0.45100334;
  double neighborhood_weight = 0.35436950;
  double late_weight = 0.03514604;
  double critical_weight = 0.28767813;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
