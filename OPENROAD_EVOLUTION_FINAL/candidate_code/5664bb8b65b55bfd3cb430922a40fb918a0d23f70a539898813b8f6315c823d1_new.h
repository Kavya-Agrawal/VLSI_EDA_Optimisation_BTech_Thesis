// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90770002;
  double density_weight = 0.14919747;
  double prefix_weight = 0.14996469;
  double neighborhood_weight = 0.37892316;
  double late_weight = 0.25582051;
  double critical_weight = 0.36599887;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
