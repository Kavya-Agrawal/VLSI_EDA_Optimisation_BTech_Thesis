// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15150190;
  double density_weight = 0.40555935;
  double prefix_weight = 0.41887396;
  double neighborhood_weight = 0.19297900;
  double late_weight = 0.20826756;
  double critical_weight = 0.41096108;
  unsigned budget = 15;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
