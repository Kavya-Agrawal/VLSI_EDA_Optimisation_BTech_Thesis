// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14756993;
  double density_weight = 0.41296563;
  double prefix_weight = 0.01644667;
  double neighborhood_weight = 0.16005191;
  double late_weight = 0.11795497;
  double critical_weight = 0.39625946;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
