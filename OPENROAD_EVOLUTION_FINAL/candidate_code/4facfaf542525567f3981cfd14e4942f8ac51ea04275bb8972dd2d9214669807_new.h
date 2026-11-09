// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19407313;
  double density_weight = 0.52558695;
  double prefix_weight = 0.28325388;
  double neighborhood_weight = 0.18273716;
  double late_weight = 0.07908771;
  double critical_weight = 0.09757393;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
