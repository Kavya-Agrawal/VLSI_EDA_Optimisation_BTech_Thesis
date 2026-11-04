// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63755046;
  double density_weight = 0.58228621;
  double prefix_weight = 0.05186317;
  double neighborhood_weight = 0.36098540;
  double late_weight = 0.14529531;
  double critical_weight = 0.31673166;
  unsigned budget = 24;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
