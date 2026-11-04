// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51900746;
  double density_weight = 0.17548311;
  double prefix_weight = 0.02953413;
  double neighborhood_weight = 0.14213281;
  double late_weight = 0.18528111;
  double critical_weight = 0.21797811;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
