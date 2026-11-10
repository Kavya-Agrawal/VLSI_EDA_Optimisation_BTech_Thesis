// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59597807;
  double density_weight = 0.11671673;
  double prefix_weight = 0.33560433;
  double neighborhood_weight = 0.11685166;
  double late_weight = 0.28750149;
  double critical_weight = 0.15034148;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
