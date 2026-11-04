// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07137660;
  double density_weight = 0.16988060;
  double prefix_weight = 0.18414586;
  double neighborhood_weight = 0.30439277;
  double late_weight = 0.28833203;
  double critical_weight = 0.33946790;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
