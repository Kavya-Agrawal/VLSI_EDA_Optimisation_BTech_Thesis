// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58214697;
  double density_weight = 0.45823775;
  double prefix_weight = 0.25282397;
  double neighborhood_weight = 0.15474395;
  double late_weight = 0.11050611;
  double critical_weight = 0.28454163;
  unsigned budget = 36;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
