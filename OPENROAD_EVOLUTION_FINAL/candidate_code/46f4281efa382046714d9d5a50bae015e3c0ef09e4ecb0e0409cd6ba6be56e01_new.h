// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56941783;
  double density_weight = 0.15410374;
  double prefix_weight = 0.41016606;
  double neighborhood_weight = 0.21560052;
  double late_weight = 0.19638797;
  double critical_weight = 0.27467407;
  unsigned budget = 25;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
