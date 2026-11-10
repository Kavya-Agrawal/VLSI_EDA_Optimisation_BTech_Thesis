// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19700615;
  double density_weight = 0.40385049;
  double prefix_weight = 0.36284282;
  double neighborhood_weight = 0.14771347;
  double late_weight = 0.20435973;
  double critical_weight = 0.15381952;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
