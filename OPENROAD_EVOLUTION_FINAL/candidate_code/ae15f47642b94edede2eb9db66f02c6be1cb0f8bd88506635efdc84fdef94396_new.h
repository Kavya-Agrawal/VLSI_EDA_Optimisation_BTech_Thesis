// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80452464;
  double density_weight = 0.36974846;
  double prefix_weight = 0.46434970;
  double neighborhood_weight = 0.39558358;
  double late_weight = 0.23213132;
  double critical_weight = 0.20395915;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
