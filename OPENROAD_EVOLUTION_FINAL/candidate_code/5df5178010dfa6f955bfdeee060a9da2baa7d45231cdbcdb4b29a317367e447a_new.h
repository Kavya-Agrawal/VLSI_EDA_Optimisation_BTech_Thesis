// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15151541;
  double density_weight = 0.13869129;
  double prefix_weight = 0.44211548;
  double neighborhood_weight = 0.02783970;
  double late_weight = 0.22816976;
  double critical_weight = 0.25513399;
  unsigned budget = 10;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
