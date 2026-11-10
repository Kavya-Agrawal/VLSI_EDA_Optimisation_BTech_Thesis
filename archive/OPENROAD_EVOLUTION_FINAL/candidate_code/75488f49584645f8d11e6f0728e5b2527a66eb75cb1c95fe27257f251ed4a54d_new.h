// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07825314;
  double density_weight = 0.45962038;
  double prefix_weight = 0.24349915;
  double neighborhood_weight = 0.15203064;
  double late_weight = 0.04180038;
  double critical_weight = 0.28701710;
  unsigned budget = 17;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
