// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00402306;
  double density_weight = 0.18634107;
  double prefix_weight = 0.11687650;
  double neighborhood_weight = 0.30812562;
  double late_weight = 0.26654919;
  double critical_weight = 0.41086880;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
