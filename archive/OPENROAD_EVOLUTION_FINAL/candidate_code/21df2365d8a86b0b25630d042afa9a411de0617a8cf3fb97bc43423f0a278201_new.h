// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34425274;
  double density_weight = 0.42047279;
  double prefix_weight = 0.15790430;
  double neighborhood_weight = 0.31622938;
  double late_weight = 0.16346198;
  double critical_weight = 0.22990948;
  unsigned budget = 5;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
