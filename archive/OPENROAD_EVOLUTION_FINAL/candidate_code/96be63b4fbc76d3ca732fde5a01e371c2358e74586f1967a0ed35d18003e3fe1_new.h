// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56011379;
  double density_weight = 0.30752715;
  double prefix_weight = 0.07317040;
  double neighborhood_weight = 0.13638090;
  double late_weight = 0.19108419;
  double critical_weight = 0.28669212;
  unsigned budget = 30;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
