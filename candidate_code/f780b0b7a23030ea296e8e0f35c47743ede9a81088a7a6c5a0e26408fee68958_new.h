// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19242573;
  double density_weight = 0.31991693;
  double prefix_weight = 0.42992642;
  double neighborhood_weight = 0.24258949;
  double late_weight = 0.15862981;
  double critical_weight = 0.31907611;
  unsigned budget = 14;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
