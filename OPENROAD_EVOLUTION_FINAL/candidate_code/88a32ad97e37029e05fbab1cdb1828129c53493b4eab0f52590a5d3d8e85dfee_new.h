// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46263780;
  double density_weight = 0.59586189;
  double prefix_weight = 0.19432138;
  double neighborhood_weight = 0.03065069;
  double late_weight = 0.04264496;
  double critical_weight = 0.32682542;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
