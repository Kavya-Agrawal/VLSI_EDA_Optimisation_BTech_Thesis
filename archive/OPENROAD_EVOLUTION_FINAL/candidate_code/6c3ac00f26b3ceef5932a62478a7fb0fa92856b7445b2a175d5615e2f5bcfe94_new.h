// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86601811;
  double density_weight = 0.08679725;
  double prefix_weight = 0.45661187;
  double neighborhood_weight = 0.24594289;
  double late_weight = 0.28051039;
  double critical_weight = 0.35170846;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
