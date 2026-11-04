// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83742589;
  double density_weight = 0.19981340;
  double prefix_weight = 0.37137775;
  double neighborhood_weight = 0.27903363;
  double late_weight = 0.00818975;
  double critical_weight = 0.03558026;
  unsigned budget = 23;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
