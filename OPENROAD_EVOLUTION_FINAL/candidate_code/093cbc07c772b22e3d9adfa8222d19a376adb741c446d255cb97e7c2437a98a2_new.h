// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23782372;
  double density_weight = 0.31357580;
  double prefix_weight = 0.02512250;
  double neighborhood_weight = 0.33327077;
  double late_weight = 0.01946979;
  double critical_weight = 0.33511345;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
