// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61434980;
  double density_weight = 0.27002162;
  double prefix_weight = 0.08996574;
  double neighborhood_weight = 0.33791788;
  double late_weight = 0.04949654;
  double critical_weight = 0.00372369;
  unsigned budget = 21;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
