// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93210409;
  double density_weight = 0.58808628;
  double prefix_weight = 0.22121475;
  double neighborhood_weight = 0.32357772;
  double late_weight = 0.20194971;
  double critical_weight = 0.21207274;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
