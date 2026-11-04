// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67837288;
  double density_weight = 0.43690691;
  double prefix_weight = 0.00602652;
  double neighborhood_weight = 0.16480662;
  double late_weight = 0.28869916;
  double critical_weight = 0.31639556;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
