// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47310173;
  double density_weight = 0.48174107;
  double prefix_weight = 0.12699619;
  double neighborhood_weight = 0.20353078;
  double late_weight = 0.03907243;
  double critical_weight = 0.01903340;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
