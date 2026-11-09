// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63055941;
  double density_weight = 0.28511844;
  double prefix_weight = 0.14702242;
  double neighborhood_weight = 0.08638728;
  double late_weight = 0.23420295;
  double critical_weight = 0.27297989;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
