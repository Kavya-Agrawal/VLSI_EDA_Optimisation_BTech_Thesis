// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48161972;
  double density_weight = 0.05627184;
  double prefix_weight = 0.39937879;
  double neighborhood_weight = 0.08122494;
  double late_weight = 0.23015726;
  double critical_weight = 0.25829225;
  unsigned budget = 37;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
