// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96676416;
  double density_weight = 0.40544716;
  double prefix_weight = 0.00080639;
  double neighborhood_weight = 0.16483252;
  double late_weight = 0.01749276;
  double critical_weight = 0.27211191;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
