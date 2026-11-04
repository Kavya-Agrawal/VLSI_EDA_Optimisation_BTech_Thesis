// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25381389;
  double density_weight = 0.28998474;
  double prefix_weight = 0.09930849;
  double neighborhood_weight = 0.14172291;
  double late_weight = 0.29386488;
  double critical_weight = 0.46428149;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
