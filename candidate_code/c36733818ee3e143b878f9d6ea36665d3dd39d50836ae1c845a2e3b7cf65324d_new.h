// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20690180;
  double density_weight = 0.35252462;
  double prefix_weight = 0.43827930;
  double neighborhood_weight = 0.04681452;
  double late_weight = 0.05228179;
  double critical_weight = 0.48706305;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
