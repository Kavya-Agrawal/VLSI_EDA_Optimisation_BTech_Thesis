// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19446318;
  double density_weight = 0.57042285;
  double prefix_weight = 0.29871179;
  double neighborhood_weight = 0.17128099;
  double late_weight = 0.09760560;
  double critical_weight = 0.35961007;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
