// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51545255;
  double density_weight = 0.21021105;
  double prefix_weight = 0.13100983;
  double neighborhood_weight = 0.30540938;
  double late_weight = 0.28866284;
  double critical_weight = 0.14440646;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
