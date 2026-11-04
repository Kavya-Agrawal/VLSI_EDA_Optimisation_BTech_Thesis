// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54594906;
  double density_weight = 0.33112273;
  double prefix_weight = 0.28884294;
  double neighborhood_weight = 0.01832705;
  double late_weight = 0.25960798;
  double critical_weight = 0.40477187;
  unsigned budget = 18;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
