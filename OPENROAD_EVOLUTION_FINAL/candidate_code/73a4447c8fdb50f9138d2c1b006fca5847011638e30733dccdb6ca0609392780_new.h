// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61669677;
  double density_weight = 0.56779580;
  double prefix_weight = 0.21583899;
  double neighborhood_weight = 0.09219027;
  double late_weight = 0.01451279;
  double critical_weight = 0.37128625;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
