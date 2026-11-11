// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59086430;
  double density_weight = 0.07621237;
  double prefix_weight = 0.18313296;
  double neighborhood_weight = 0.18804943;
  double late_weight = 0.00352796;
  double critical_weight = 0.28448655;
  unsigned budget = 7;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
