// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12312321;
  double density_weight = 0.43407670;
  double prefix_weight = 0.17734064;
  double neighborhood_weight = 0.28966151;
  double late_weight = 0.18346964;
  double critical_weight = 0.40422563;
  unsigned budget = 35;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
