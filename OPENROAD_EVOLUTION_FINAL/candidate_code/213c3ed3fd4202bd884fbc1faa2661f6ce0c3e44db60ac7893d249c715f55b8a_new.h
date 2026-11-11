// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82956536;
  double density_weight = 0.14714455;
  double prefix_weight = 0.20999485;
  double neighborhood_weight = 0.05762410;
  double late_weight = 0.06825094;
  double critical_weight = 0.45818650;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
