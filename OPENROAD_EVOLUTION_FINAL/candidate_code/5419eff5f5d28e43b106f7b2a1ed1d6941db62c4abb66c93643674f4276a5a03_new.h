// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03313356;
  double density_weight = 0.17714183;
  double prefix_weight = 0.00887010;
  double neighborhood_weight = 0.36155203;
  double late_weight = 0.03910127;
  double critical_weight = 0.10375573;
  unsigned budget = 31;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
