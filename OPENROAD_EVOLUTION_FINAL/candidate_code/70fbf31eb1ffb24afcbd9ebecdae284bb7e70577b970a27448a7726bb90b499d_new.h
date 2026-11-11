// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74511747;
  double density_weight = 0.12754769;
  double prefix_weight = 0.04829819;
  double neighborhood_weight = 0.18401539;
  double late_weight = 0.03582683;
  double critical_weight = 0.03286222;
  unsigned budget = 34;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
