// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72356318;
  double density_weight = 0.50637099;
  double prefix_weight = 0.20068395;
  double neighborhood_weight = 0.28200451;
  double late_weight = 0.23696031;
  double critical_weight = 0.21240376;
  unsigned budget = 9;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
