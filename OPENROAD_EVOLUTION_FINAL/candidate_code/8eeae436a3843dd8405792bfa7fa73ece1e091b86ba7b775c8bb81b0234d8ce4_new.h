// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94481731;
  double density_weight = 0.02272836;
  double prefix_weight = 0.44137396;
  double neighborhood_weight = 0.03812591;
  double late_weight = 0.21564886;
  double critical_weight = 0.03042953;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
