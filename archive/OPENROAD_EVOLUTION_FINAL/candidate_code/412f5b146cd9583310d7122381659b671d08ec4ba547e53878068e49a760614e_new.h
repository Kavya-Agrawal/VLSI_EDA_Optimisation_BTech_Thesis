// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46975620;
  double density_weight = 0.39474442;
  double prefix_weight = 0.48213039;
  double neighborhood_weight = 0.17040117;
  double late_weight = 0.19557449;
  double critical_weight = 0.42160193;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
