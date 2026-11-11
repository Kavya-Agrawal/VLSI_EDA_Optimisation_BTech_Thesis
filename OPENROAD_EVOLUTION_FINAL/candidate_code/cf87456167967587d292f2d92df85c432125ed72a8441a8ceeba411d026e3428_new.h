// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57716608;
  double density_weight = 0.20921576;
  double prefix_weight = 0.19188418;
  double neighborhood_weight = 0.07096866;
  double late_weight = 0.26080929;
  double critical_weight = 0.37714303;
  unsigned budget = 5;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
