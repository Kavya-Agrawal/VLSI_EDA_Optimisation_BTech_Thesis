// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09390829;
  double density_weight = 0.11209672;
  double prefix_weight = 0.28973218;
  double neighborhood_weight = 0.10247236;
  double late_weight = 0.03871208;
  double critical_weight = 0.25485607;
  unsigned budget = 5;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
