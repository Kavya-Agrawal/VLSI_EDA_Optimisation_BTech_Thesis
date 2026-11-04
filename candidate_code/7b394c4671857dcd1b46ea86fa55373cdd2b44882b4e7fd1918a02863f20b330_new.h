// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84196077;
  double density_weight = 0.58009013;
  double prefix_weight = 0.09936305;
  double neighborhood_weight = 0.30192656;
  double late_weight = 0.24068014;
  double critical_weight = 0.30759130;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
