// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61223931;
  double density_weight = 0.43746838;
  double prefix_weight = 0.05442163;
  double neighborhood_weight = 0.04334972;
  double late_weight = 0.10449076;
  double critical_weight = 0.00575928;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
