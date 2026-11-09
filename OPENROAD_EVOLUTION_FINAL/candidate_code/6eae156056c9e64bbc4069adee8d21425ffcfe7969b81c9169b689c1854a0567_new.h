// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65349512;
  double density_weight = 0.36306117;
  double prefix_weight = 0.04240320;
  double neighborhood_weight = 0.10536560;
  double late_weight = 0.16601898;
  double critical_weight = 0.33417486;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
