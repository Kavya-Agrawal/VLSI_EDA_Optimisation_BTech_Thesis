// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28357290;
  double density_weight = 0.47675397;
  double prefix_weight = 0.40279379;
  double neighborhood_weight = 0.18672431;
  double late_weight = 0.21986574;
  double critical_weight = 0.46078678;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
