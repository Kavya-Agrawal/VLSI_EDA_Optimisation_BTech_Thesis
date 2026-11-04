// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37976850;
  double density_weight = 0.48034541;
  double prefix_weight = 0.37073999;
  double neighborhood_weight = 0.30590261;
  double late_weight = 0.08383800;
  double critical_weight = 0.26479455;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
