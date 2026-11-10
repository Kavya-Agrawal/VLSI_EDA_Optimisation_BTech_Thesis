// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45472922;
  double density_weight = 0.52869387;
  double prefix_weight = 0.25749984;
  double neighborhood_weight = 0.09417378;
  double late_weight = 0.16677512;
  double critical_weight = 0.42730031;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
