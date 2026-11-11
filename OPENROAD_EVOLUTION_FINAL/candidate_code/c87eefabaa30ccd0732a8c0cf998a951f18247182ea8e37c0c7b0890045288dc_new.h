// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16060586;
  double density_weight = 0.58295581;
  double prefix_weight = 0.41072596;
  double neighborhood_weight = 0.30539966;
  double late_weight = 0.00311262;
  double critical_weight = 0.30434762;
  unsigned budget = 29;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
