// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80399835;
  double density_weight = 0.35842167;
  double prefix_weight = 0.44866506;
  double neighborhood_weight = 0.11596696;
  double late_weight = 0.03208665;
  double critical_weight = 0.08118005;
  unsigned budget = 29;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
