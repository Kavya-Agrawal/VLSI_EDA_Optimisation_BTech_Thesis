// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56045524;
  double density_weight = 0.08256958;
  double prefix_weight = 0.01776344;
  double neighborhood_weight = 0.16168784;
  double late_weight = 0.15842215;
  double critical_weight = 0.44982309;
  unsigned budget = 9;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
