// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66174458;
  double density_weight = 0.02511989;
  double prefix_weight = 0.37591101;
  double neighborhood_weight = 0.23284074;
  double late_weight = 0.08832026;
  double critical_weight = 0.13771568;
  unsigned budget = 18;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
