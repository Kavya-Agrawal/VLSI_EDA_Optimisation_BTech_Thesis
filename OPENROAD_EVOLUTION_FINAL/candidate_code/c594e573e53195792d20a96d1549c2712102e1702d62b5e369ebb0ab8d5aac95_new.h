// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43420753;
  double density_weight = 0.56486938;
  double prefix_weight = 0.05075300;
  double neighborhood_weight = 0.30804178;
  double late_weight = 0.16151905;
  double critical_weight = 0.17887116;
  unsigned budget = 9;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
