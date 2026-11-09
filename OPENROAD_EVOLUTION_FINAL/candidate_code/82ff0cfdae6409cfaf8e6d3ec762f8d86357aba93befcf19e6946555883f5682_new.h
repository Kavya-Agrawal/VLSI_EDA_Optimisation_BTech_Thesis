// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09073640;
  double density_weight = 0.21740312;
  double prefix_weight = 0.24249406;
  double neighborhood_weight = 0.18790220;
  double late_weight = 0.16561661;
  double critical_weight = 0.39094007;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
