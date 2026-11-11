// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79179058;
  double density_weight = 0.44882100;
  double prefix_weight = 0.34554282;
  double neighborhood_weight = 0.34452335;
  double late_weight = 0.27376059;
  double critical_weight = 0.11042329;
  unsigned budget = 25;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
