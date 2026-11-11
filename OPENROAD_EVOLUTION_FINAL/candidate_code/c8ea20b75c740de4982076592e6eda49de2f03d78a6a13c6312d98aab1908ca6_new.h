// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31156229;
  double density_weight = 0.13254622;
  double prefix_weight = 0.04879653;
  double neighborhood_weight = 0.03687574;
  double late_weight = 0.03320709;
  double critical_weight = 0.01881026;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
