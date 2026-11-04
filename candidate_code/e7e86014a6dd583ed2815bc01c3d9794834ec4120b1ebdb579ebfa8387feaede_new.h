// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66154249;
  double density_weight = 0.03221338;
  double prefix_weight = 0.32870273;
  double neighborhood_weight = 0.34183350;
  double late_weight = 0.19421680;
  double critical_weight = 0.18173119;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
