// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80278709;
  double density_weight = 0.09737985;
  double prefix_weight = 0.15554982;
  double neighborhood_weight = 0.35581090;
  double late_weight = 0.16845362;
  double critical_weight = 0.06639210;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
