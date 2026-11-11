// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96096125;
  double density_weight = 0.55136643;
  double prefix_weight = 0.17589584;
  double neighborhood_weight = 0.27696530;
  double late_weight = 0.00417968;
  double critical_weight = 0.02497655;
  unsigned budget = 38;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
