// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61428409;
  double density_weight = 0.08079374;
  double prefix_weight = 0.07528326;
  double neighborhood_weight = 0.03373021;
  double late_weight = 0.06522896;
  double critical_weight = 0.04034331;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
