// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28567799;
  double density_weight = 0.46393962;
  double prefix_weight = 0.32509052;
  double neighborhood_weight = 0.13414892;
  double late_weight = 0.14338530;
  double critical_weight = 0.21153052;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
