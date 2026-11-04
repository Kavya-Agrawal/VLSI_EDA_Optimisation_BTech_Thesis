// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93877836;
  double density_weight = 0.05748804;
  double prefix_weight = 0.37100564;
  double neighborhood_weight = 0.27667429;
  double late_weight = 0.04466190;
  double critical_weight = 0.22607578;
  unsigned budget = 9;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
