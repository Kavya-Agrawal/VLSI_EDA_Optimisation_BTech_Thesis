// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09349730;
  double density_weight = 0.29675370;
  double prefix_weight = 0.01601331;
  double neighborhood_weight = 0.16565369;
  double late_weight = 0.19155930;
  double critical_weight = 0.05816722;
  unsigned budget = 33;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
