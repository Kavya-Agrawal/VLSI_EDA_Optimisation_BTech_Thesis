// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57927794;
  double density_weight = 0.45558298;
  double prefix_weight = 0.30107096;
  double neighborhood_weight = 0.10815074;
  double late_weight = 0.18650959;
  double critical_weight = 0.38118276;
  unsigned budget = 7;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
