// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80181830;
  double density_weight = 0.37764160;
  double prefix_weight = 0.18492328;
  double neighborhood_weight = 0.26858767;
  double late_weight = 0.01777213;
  double critical_weight = 0.30656992;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
