// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43752380;
  double density_weight = 0.14701472;
  double prefix_weight = 0.27416091;
  double neighborhood_weight = 0.30907212;
  double late_weight = 0.21842877;
  double critical_weight = 0.44684070;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
