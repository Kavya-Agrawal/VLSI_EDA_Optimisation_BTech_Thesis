// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51478811;
  double density_weight = 0.35054832;
  double prefix_weight = 0.32924320;
  double neighborhood_weight = 0.13139497;
  double late_weight = 0.01131923;
  double critical_weight = 0.20846691;
  unsigned budget = 34;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
