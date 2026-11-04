// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61730098;
  double density_weight = 0.41982767;
  double prefix_weight = 0.36498442;
  double neighborhood_weight = 0.20329960;
  double late_weight = 0.29315967;
  double critical_weight = 0.31728991;
  unsigned budget = 23;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
