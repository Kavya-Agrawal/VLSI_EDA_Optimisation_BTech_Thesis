// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91030791;
  double density_weight = 0.27668887;
  double prefix_weight = 0.38970426;
  double neighborhood_weight = 0.37921221;
  double late_weight = 0.29779014;
  double critical_weight = 0.08649987;
  unsigned budget = 37;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
