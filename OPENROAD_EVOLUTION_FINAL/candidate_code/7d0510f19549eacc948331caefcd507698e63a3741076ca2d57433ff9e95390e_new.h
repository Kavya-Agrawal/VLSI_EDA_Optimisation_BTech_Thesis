// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65288857;
  double density_weight = 0.48910011;
  double prefix_weight = 0.28477172;
  double neighborhood_weight = 0.16186730;
  double late_weight = 0.15244598;
  double critical_weight = 0.20802214;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
