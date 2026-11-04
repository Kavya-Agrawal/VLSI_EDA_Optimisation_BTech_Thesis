// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21997395;
  double density_weight = 0.27179127;
  double prefix_weight = 0.18557529;
  double neighborhood_weight = 0.02004084;
  double late_weight = 0.02188615;
  double critical_weight = 0.38722187;
  unsigned budget = 13;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
