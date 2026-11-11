// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16102244;
  double density_weight = 0.47380826;
  double prefix_weight = 0.05226616;
  double neighborhood_weight = 0.06452016;
  double late_weight = 0.01174594;
  double critical_weight = 0.41438954;
  unsigned budget = 19;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
