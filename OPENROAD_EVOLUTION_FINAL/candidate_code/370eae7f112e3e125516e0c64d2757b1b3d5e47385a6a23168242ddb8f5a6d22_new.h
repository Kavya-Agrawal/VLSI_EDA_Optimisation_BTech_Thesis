// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19964705;
  double density_weight = 0.28841910;
  double prefix_weight = 0.05068359;
  double neighborhood_weight = 0.05281137;
  double late_weight = 0.00898576;
  double critical_weight = 0.06896481;
  unsigned budget = 16;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
