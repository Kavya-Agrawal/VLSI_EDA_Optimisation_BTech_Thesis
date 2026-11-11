// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07773783;
  double density_weight = 0.16745678;
  double prefix_weight = 0.00904044;
  double neighborhood_weight = 0.31783984;
  double late_weight = 0.17379332;
  double critical_weight = 0.41953650;
  unsigned budget = 36;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
