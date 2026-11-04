// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21382799;
  double density_weight = 0.49960076;
  double prefix_weight = 0.28729579;
  double neighborhood_weight = 0.32312541;
  double late_weight = 0.07157384;
  double critical_weight = 0.39699898;
  unsigned budget = 38;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
