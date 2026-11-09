// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47492464;
  double density_weight = 0.46529028;
  double prefix_weight = 0.04264772;
  double neighborhood_weight = 0.31188351;
  double late_weight = 0.12386828;
  double critical_weight = 0.02523449;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
