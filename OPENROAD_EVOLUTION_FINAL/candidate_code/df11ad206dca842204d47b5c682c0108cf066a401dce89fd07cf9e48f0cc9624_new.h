// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87635718;
  double density_weight = 0.14640032;
  double prefix_weight = 0.42180283;
  double neighborhood_weight = 0.18107298;
  double late_weight = 0.12479239;
  double critical_weight = 0.01060327;
  unsigned budget = 9;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
