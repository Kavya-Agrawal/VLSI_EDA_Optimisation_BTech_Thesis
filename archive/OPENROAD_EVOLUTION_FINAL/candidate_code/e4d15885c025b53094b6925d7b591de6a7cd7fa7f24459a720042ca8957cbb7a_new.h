// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46217098;
  double density_weight = 0.29253669;
  double prefix_weight = 0.01515810;
  double neighborhood_weight = 0.19254181;
  double late_weight = 0.27333471;
  double critical_weight = 0.09890266;
  unsigned budget = 38;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
