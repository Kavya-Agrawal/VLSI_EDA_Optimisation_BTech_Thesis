// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43831126;
  double density_weight = 0.02536194;
  double prefix_weight = 0.32873941;
  double neighborhood_weight = 0.35740047;
  double late_weight = 0.09715896;
  double critical_weight = 0.02206956;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
