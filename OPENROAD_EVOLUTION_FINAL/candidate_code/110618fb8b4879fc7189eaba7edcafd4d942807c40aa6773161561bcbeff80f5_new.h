// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04788035;
  double density_weight = 0.49154652;
  double prefix_weight = 0.47990393;
  double neighborhood_weight = 0.11956955;
  double late_weight = 0.19047045;
  double critical_weight = 0.11204168;
  unsigned budget = 17;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
