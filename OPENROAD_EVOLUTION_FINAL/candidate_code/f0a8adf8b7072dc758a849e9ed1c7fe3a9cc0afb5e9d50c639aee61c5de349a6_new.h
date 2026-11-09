// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49865801;
  double density_weight = 0.08402979;
  double prefix_weight = 0.36011792;
  double neighborhood_weight = 0.02679890;
  double late_weight = 0.00164120;
  double critical_weight = 0.02936448;
  unsigned budget = 15;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
