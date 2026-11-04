// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17563356;
  double density_weight = 0.39787012;
  double prefix_weight = 0.16164646;
  double neighborhood_weight = 0.38461072;
  double late_weight = 0.17380267;
  double critical_weight = 0.04412217;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
