// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48353742;
  double density_weight = 0.54190371;
  double prefix_weight = 0.19895586;
  double neighborhood_weight = 0.05015928;
  double late_weight = 0.28301322;
  double critical_weight = 0.25565397;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
