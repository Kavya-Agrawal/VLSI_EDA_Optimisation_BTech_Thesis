// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21494321;
  double density_weight = 0.20749105;
  double prefix_weight = 0.24442922;
  double neighborhood_weight = 0.05027991;
  double late_weight = 0.20265698;
  double critical_weight = 0.36596968;
  unsigned budget = 40;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
