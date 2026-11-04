// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66923681;
  double density_weight = 0.07608379;
  double prefix_weight = 0.35201555;
  double neighborhood_weight = 0.35400997;
  double late_weight = 0.14524787;
  double critical_weight = 0.01128505;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
