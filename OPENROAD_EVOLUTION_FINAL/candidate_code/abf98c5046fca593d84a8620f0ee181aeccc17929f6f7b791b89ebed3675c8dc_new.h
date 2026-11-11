// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86908599;
  double density_weight = 0.30390343;
  double prefix_weight = 0.22381166;
  double neighborhood_weight = 0.24935780;
  double late_weight = 0.09964783;
  double critical_weight = 0.25742610;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
