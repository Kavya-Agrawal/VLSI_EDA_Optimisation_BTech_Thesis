// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71799216;
  double density_weight = 0.51316045;
  double prefix_weight = 0.37978126;
  double neighborhood_weight = 0.26858002;
  double late_weight = 0.15855396;
  double critical_weight = 0.37412173;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
