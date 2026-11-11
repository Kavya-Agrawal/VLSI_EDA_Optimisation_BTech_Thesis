// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38318558;
  double density_weight = 0.58883924;
  double prefix_weight = 0.25856960;
  double neighborhood_weight = 0.06154167;
  double late_weight = 0.29059475;
  double critical_weight = 0.43359259;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
