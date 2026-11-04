// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07928021;
  double density_weight = 0.02248388;
  double prefix_weight = 0.24112594;
  double neighborhood_weight = 0.33095474;
  double late_weight = 0.15428810;
  double critical_weight = 0.49696760;
  unsigned budget = 4;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
