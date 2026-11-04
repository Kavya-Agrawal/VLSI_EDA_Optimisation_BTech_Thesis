// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24053729;
  double density_weight = 0.18312318;
  double prefix_weight = 0.16739248;
  double neighborhood_weight = 0.13086233;
  double late_weight = 0.15224648;
  double critical_weight = 0.09445477;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
