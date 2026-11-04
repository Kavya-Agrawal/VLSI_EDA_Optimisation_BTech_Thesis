// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79169477;
  double density_weight = 0.27735554;
  double prefix_weight = 0.07180881;
  double neighborhood_weight = 0.33814263;
  double late_weight = 0.00827400;
  double critical_weight = 0.21142831;
  unsigned budget = 34;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
