// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89239331;
  double density_weight = 0.17030183;
  double prefix_weight = 0.39537682;
  double neighborhood_weight = 0.00307213;
  double late_weight = 0.19484475;
  double critical_weight = 0.31523161;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
