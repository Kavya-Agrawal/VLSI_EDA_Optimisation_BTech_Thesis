// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84319652;
  double density_weight = 0.53677252;
  double prefix_weight = 0.42426541;
  double neighborhood_weight = 0.18393494;
  double late_weight = 0.24430384;
  double critical_weight = 0.01496145;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
