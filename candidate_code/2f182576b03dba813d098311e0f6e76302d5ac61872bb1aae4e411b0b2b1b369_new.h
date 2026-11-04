// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86431679;
  double density_weight = 0.06482616;
  double prefix_weight = 0.09424415;
  double neighborhood_weight = 0.22066288;
  double late_weight = 0.01447794;
  double critical_weight = 0.05881299;
  unsigned budget = 33;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
