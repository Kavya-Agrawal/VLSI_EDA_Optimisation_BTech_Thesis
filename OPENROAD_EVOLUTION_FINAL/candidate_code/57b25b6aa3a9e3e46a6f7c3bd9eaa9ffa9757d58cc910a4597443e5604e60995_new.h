// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29945712;
  double density_weight = 0.42809092;
  double prefix_weight = 0.11292174;
  double neighborhood_weight = 0.18437534;
  double late_weight = 0.24579352;
  double critical_weight = 0.18994299;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
