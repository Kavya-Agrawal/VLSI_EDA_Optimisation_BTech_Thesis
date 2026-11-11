// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10168743;
  double density_weight = 0.53728328;
  double prefix_weight = 0.13849355;
  double neighborhood_weight = 0.17959637;
  double late_weight = 0.22141024;
  double critical_weight = 0.13772544;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
