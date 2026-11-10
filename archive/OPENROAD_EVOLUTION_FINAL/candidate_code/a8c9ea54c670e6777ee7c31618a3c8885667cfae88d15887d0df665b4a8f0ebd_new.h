// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21337188;
  double density_weight = 0.54987101;
  double prefix_weight = 0.15589535;
  double neighborhood_weight = 0.04377608;
  double late_weight = 0.02381096;
  double critical_weight = 0.21610906;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
