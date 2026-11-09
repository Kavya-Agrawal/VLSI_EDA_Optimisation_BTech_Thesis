// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80839809;
  double density_weight = 0.19481496;
  double prefix_weight = 0.26136104;
  double neighborhood_weight = 0.30253186;
  double late_weight = 0.09348319;
  double critical_weight = 0.12773937;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
