// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51346676;
  double density_weight = 0.29812411;
  double prefix_weight = 0.06270817;
  double neighborhood_weight = 0.15258618;
  double late_weight = 0.03332820;
  double critical_weight = 0.05688347;
  unsigned budget = 38;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
