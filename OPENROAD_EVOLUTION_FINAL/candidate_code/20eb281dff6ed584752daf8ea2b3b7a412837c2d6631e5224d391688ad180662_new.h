// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79242832;
  double density_weight = 0.15101792;
  double prefix_weight = 0.06620777;
  double neighborhood_weight = 0.11596706;
  double late_weight = 0.04987125;
  double critical_weight = 0.38137129;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
