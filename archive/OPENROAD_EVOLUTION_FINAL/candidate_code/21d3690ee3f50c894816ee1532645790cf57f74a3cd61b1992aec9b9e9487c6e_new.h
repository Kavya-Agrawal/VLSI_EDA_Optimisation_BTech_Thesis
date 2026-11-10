// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99447919;
  double density_weight = 0.23979378;
  double prefix_weight = 0.09263516;
  double neighborhood_weight = 0.04332137;
  double late_weight = 0.08788747;
  double critical_weight = 0.33486825;
  unsigned budget = 28;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
