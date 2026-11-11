// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37743497;
  double density_weight = 0.28772186;
  double prefix_weight = 0.12359782;
  double neighborhood_weight = 0.33145611;
  double late_weight = 0.16996177;
  double critical_weight = 0.48073627;
  unsigned budget = 4;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
