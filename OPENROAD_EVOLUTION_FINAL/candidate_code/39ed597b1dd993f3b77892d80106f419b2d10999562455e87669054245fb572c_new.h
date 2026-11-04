// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96383019;
  double density_weight = 0.55376867;
  double prefix_weight = 0.04065462;
  double neighborhood_weight = 0.18694506;
  double late_weight = 0.10301617;
  double critical_weight = 0.31995390;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
