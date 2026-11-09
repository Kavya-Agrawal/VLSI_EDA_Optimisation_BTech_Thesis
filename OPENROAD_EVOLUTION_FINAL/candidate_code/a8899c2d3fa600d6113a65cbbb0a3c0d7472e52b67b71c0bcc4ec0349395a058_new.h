// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60193420;
  double density_weight = 0.47146247;
  double prefix_weight = 0.16310889;
  double neighborhood_weight = 0.31313191;
  double late_weight = 0.18854419;
  double critical_weight = 0.41522729;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
