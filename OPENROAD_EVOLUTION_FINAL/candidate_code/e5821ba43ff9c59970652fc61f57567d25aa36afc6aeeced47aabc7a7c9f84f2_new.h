// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70059697;
  double density_weight = 0.57858965;
  double prefix_weight = 0.05550239;
  double neighborhood_weight = 0.15860892;
  double late_weight = 0.29304471;
  double critical_weight = 0.42204210;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
