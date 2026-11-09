// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61293896;
  double density_weight = 0.46071821;
  double prefix_weight = 0.28551798;
  double neighborhood_weight = 0.11924236;
  double late_weight = 0.04662925;
  double critical_weight = 0.35772631;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
