// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92430332;
  double density_weight = 0.48350406;
  double prefix_weight = 0.36580885;
  double neighborhood_weight = 0.28213618;
  double late_weight = 0.04660280;
  double critical_weight = 0.04901420;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
