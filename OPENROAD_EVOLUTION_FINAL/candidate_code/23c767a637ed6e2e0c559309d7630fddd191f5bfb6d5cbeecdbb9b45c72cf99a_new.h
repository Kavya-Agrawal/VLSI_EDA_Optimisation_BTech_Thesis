// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12281608;
  double density_weight = 0.22801955;
  double prefix_weight = 0.21821393;
  double neighborhood_weight = 0.16040511;
  double late_weight = 0.02060391;
  double critical_weight = 0.33513011;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
