// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46860398;
  double density_weight = 0.33474359;
  double prefix_weight = 0.48136003;
  double neighborhood_weight = 0.27918475;
  double late_weight = 0.10459103;
  double critical_weight = 0.00879142;
  unsigned budget = 23;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
