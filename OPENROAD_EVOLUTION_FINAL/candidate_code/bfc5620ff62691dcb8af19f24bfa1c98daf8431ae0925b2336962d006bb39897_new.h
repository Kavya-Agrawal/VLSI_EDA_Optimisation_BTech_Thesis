// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08977196;
  double density_weight = 0.10697842;
  double prefix_weight = 0.28999953;
  double neighborhood_weight = 0.33920863;
  double late_weight = 0.29834816;
  double critical_weight = 0.20043866;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
