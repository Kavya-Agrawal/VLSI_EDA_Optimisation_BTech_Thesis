// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13098986;
  double density_weight = 0.29147944;
  double prefix_weight = 0.04241095;
  double neighborhood_weight = 0.30272316;
  double late_weight = 0.19246692;
  double critical_weight = 0.47090680;
  unsigned budget = 12;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
