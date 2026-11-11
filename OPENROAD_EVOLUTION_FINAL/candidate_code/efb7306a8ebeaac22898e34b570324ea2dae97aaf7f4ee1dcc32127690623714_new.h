// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72246039;
  double density_weight = 0.44468164;
  double prefix_weight = 0.05388223;
  double neighborhood_weight = 0.32244296;
  double late_weight = 0.12584989;
  double critical_weight = 0.03693124;
  unsigned budget = 24;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
