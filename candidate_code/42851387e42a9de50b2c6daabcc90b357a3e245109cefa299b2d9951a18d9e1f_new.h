// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79734178;
  double density_weight = 0.20695075;
  double prefix_weight = 0.06159823;
  double neighborhood_weight = 0.13826005;
  double late_weight = 0.28382619;
  double critical_weight = 0.09493983;
  unsigned budget = 31;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
