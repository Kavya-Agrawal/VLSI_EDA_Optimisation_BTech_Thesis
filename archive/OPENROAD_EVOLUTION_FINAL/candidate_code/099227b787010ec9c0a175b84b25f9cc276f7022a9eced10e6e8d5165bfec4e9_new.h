// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73539023;
  double density_weight = 0.31442098;
  double prefix_weight = 0.15882173;
  double neighborhood_weight = 0.08772498;
  double late_weight = 0.13532973;
  double critical_weight = 0.05120388;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
