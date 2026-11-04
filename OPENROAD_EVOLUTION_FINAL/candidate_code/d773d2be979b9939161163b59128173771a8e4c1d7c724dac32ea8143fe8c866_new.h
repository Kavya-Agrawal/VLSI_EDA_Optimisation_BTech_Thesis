// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28835366;
  double density_weight = 0.03772130;
  double prefix_weight = 0.23512783;
  double neighborhood_weight = 0.14688735;
  double late_weight = 0.16067296;
  double critical_weight = 0.24291222;
  unsigned budget = 37;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
