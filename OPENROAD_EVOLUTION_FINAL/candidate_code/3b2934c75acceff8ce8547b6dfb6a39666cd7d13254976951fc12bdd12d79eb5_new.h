// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66457633;
  double density_weight = 0.41408515;
  double prefix_weight = 0.40573301;
  double neighborhood_weight = 0.37644388;
  double late_weight = 0.11494157;
  double critical_weight = 0.34297276;
  unsigned budget = 27;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
