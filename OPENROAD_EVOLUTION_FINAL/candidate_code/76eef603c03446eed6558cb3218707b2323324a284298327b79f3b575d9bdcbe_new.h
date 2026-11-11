// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74945901;
  double density_weight = 0.27807103;
  double prefix_weight = 0.48104785;
  double neighborhood_weight = 0.02663577;
  double late_weight = 0.08097148;
  double critical_weight = 0.43236337;
  unsigned budget = 15;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
