// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70330049;
  double density_weight = 0.35992682;
  double prefix_weight = 0.47383262;
  double neighborhood_weight = 0.00218434;
  double late_weight = 0.28575900;
  double critical_weight = 0.16798586;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
