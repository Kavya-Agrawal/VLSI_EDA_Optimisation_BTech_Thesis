// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28496232;
  double density_weight = 0.51866627;
  double prefix_weight = 0.25285104;
  double neighborhood_weight = 0.06172443;
  double late_weight = 0.17529699;
  double critical_weight = 0.13881169;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
