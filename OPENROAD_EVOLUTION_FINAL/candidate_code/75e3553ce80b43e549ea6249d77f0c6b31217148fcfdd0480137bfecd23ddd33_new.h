// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71993220;
  double density_weight = 0.19515947;
  double prefix_weight = 0.19952526;
  double neighborhood_weight = 0.39467282;
  double late_weight = 0.10281478;
  double critical_weight = 0.04335725;
  unsigned budget = 36;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
