// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99565146;
  double density_weight = 0.45862918;
  double prefix_weight = 0.03379388;
  double neighborhood_weight = 0.33134477;
  double late_weight = 0.17015039;
  double critical_weight = 0.42509415;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
