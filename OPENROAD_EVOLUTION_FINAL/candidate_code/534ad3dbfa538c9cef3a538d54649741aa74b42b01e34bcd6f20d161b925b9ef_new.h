// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97743866;
  double density_weight = 0.20828409;
  double prefix_weight = 0.27663293;
  double neighborhood_weight = 0.25026924;
  double late_weight = 0.25259791;
  double critical_weight = 0.26640408;
  unsigned budget = 25;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
