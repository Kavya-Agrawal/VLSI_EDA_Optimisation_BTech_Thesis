// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79193810;
  double density_weight = 0.57622561;
  double prefix_weight = 0.03460907;
  double neighborhood_weight = 0.34254228;
  double late_weight = 0.20447025;
  double critical_weight = 0.42526156;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
