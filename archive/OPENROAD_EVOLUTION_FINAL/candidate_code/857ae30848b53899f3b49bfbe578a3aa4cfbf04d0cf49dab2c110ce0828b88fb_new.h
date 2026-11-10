// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36556223;
  double density_weight = 0.40185822;
  double prefix_weight = 0.35112942;
  double neighborhood_weight = 0.15559821;
  double late_weight = 0.19128410;
  double critical_weight = 0.08757044;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
