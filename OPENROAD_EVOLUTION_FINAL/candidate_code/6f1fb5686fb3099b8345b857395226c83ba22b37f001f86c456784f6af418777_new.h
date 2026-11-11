// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35794046;
  double density_weight = 0.35881802;
  double prefix_weight = 0.35620637;
  double neighborhood_weight = 0.19398690;
  double late_weight = 0.05702848;
  double critical_weight = 0.33161267;
  unsigned budget = 38;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
