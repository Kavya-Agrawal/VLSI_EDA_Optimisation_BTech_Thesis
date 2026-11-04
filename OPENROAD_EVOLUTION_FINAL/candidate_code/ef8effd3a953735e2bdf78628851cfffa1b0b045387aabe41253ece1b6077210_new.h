// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56695009;
  double density_weight = 0.51203268;
  double prefix_weight = 0.48806605;
  double neighborhood_weight = 0.31223163;
  double late_weight = 0.15486128;
  double critical_weight = 0.03306255;
  unsigned budget = 36;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
