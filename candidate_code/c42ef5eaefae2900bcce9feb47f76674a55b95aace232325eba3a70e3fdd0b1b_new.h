// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11196483;
  double density_weight = 0.43227567;
  double prefix_weight = 0.21112058;
  double neighborhood_weight = 0.16655569;
  double late_weight = 0.05645273;
  double critical_weight = 0.19585481;
  unsigned budget = 10;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
