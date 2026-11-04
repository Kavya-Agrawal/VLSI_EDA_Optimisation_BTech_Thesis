// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16648236;
  double density_weight = 0.55492002;
  double prefix_weight = 0.02473171;
  double neighborhood_weight = 0.12442657;
  double late_weight = 0.28020134;
  double critical_weight = 0.42302196;
  unsigned budget = 21;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
