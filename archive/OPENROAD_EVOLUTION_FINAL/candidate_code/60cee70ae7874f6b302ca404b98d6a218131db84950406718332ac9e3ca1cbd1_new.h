// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96514903;
  double density_weight = 0.09991683;
  double prefix_weight = 0.38549770;
  double neighborhood_weight = 0.05450671;
  double late_weight = 0.22426247;
  double critical_weight = 0.13379391;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
