// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50257995;
  double density_weight = 0.56956410;
  double prefix_weight = 0.00929405;
  double neighborhood_weight = 0.11066075;
  double late_weight = 0.27398947;
  double critical_weight = 0.27365978;
  unsigned budget = 30;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
