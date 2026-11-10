// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44557596;
  double density_weight = 0.01958324;
  double prefix_weight = 0.43457520;
  double neighborhood_weight = 0.01792541;
  double late_weight = 0.04426991;
  double critical_weight = 0.26498867;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
