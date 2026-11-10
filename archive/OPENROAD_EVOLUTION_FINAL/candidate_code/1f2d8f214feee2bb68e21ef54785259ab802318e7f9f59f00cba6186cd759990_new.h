// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37234003;
  double density_weight = 0.00118207;
  double prefix_weight = 0.10637990;
  double neighborhood_weight = 0.04130603;
  double late_weight = 0.07298867;
  double critical_weight = 0.15166421;
  unsigned budget = 4;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
