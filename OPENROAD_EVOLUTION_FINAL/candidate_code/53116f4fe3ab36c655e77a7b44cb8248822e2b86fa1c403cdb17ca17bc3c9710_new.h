// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59792093;
  double density_weight = 0.29166600;
  double prefix_weight = 0.00135230;
  double neighborhood_weight = 0.36733245;
  double late_weight = 0.06386042;
  double critical_weight = 0.03362887;
  unsigned budget = 15;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
