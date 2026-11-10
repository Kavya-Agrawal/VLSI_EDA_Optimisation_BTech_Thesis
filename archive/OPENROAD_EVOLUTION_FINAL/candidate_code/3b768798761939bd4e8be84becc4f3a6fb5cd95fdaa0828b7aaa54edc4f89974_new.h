// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44947782;
  double density_weight = 0.22761314;
  double prefix_weight = 0.45700468;
  double neighborhood_weight = 0.01996735;
  double late_weight = 0.04848516;
  double critical_weight = 0.11865494;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
