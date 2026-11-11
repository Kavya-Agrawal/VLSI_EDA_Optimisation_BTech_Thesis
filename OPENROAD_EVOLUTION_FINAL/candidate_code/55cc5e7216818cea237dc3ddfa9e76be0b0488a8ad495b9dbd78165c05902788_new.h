// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14127249;
  double density_weight = 0.53814170;
  double prefix_weight = 0.46441508;
  double neighborhood_weight = 0.33125041;
  double late_weight = 0.21027805;
  double critical_weight = 0.11934457;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
