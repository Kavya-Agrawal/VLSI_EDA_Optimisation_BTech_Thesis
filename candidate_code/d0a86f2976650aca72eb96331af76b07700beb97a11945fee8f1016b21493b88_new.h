// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66260056;
  double density_weight = 0.39882813;
  double prefix_weight = 0.20395011;
  double neighborhood_weight = 0.13505854;
  double late_weight = 0.01261787;
  double critical_weight = 0.32829116;
  unsigned budget = 22;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
