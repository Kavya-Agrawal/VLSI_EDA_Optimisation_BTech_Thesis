// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01496130;
  double density_weight = 0.58878957;
  double prefix_weight = 0.15732396;
  double neighborhood_weight = 0.36331143;
  double late_weight = 0.10300447;
  double critical_weight = 0.31828118;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
