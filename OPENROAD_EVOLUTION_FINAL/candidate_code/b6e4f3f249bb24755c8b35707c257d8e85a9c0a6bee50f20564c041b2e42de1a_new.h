// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34190824;
  double density_weight = 0.46147621;
  double prefix_weight = 0.13220149;
  double neighborhood_weight = 0.32632853;
  double late_weight = 0.17181519;
  double critical_weight = 0.11926015;
  unsigned budget = 12;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
