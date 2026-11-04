// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25554402;
  double density_weight = 0.44836413;
  double prefix_weight = 0.30836357;
  double neighborhood_weight = 0.33788284;
  double late_weight = 0.14729951;
  double critical_weight = 0.38897372;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
