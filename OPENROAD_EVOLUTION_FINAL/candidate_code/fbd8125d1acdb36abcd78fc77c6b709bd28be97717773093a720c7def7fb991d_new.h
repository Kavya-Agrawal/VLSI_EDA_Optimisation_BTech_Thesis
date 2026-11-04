// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16258290;
  double density_weight = 0.03771830;
  double prefix_weight = 0.47380896;
  double neighborhood_weight = 0.00851273;
  double late_weight = 0.00541122;
  double critical_weight = 0.42133654;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
