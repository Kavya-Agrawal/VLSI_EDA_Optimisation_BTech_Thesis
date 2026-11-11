// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10931702;
  double density_weight = 0.09103921;
  double prefix_weight = 0.09597269;
  double neighborhood_weight = 0.32894969;
  double late_weight = 0.01936041;
  double critical_weight = 0.43528110;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
