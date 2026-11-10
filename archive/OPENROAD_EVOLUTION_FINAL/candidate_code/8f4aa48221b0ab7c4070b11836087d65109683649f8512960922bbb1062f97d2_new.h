// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66004436;
  double density_weight = 0.51953574;
  double prefix_weight = 0.09703257;
  double neighborhood_weight = 0.11834949;
  double late_weight = 0.02798783;
  double critical_weight = 0.49946420;
  unsigned budget = 8;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
