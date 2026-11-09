// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72112866;
  double density_weight = 0.41987152;
  double prefix_weight = 0.43827354;
  double neighborhood_weight = 0.25242484;
  double late_weight = 0.17483220;
  double critical_weight = 0.25997285;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
