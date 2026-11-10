// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18059312;
  double density_weight = 0.51860159;
  double prefix_weight = 0.19760922;
  double neighborhood_weight = 0.30328317;
  double late_weight = 0.05923549;
  double critical_weight = 0.01767332;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
