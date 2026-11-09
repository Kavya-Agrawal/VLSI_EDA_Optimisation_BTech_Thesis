// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38414338;
  double density_weight = 0.33350347;
  double prefix_weight = 0.24345661;
  double neighborhood_weight = 0.16159111;
  double late_weight = 0.00443384;
  double critical_weight = 0.05872735;
  unsigned budget = 16;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
