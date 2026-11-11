// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51038894;
  double density_weight = 0.12947810;
  double prefix_weight = 0.30163934;
  double neighborhood_weight = 0.35025448;
  double late_weight = 0.02816932;
  double critical_weight = 0.21232352;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
