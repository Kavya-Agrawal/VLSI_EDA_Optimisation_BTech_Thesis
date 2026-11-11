// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93292458;
  double density_weight = 0.41502378;
  double prefix_weight = 0.47770747;
  double neighborhood_weight = 0.05881524;
  double late_weight = 0.10155936;
  double critical_weight = 0.25422498;
  unsigned budget = 14;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
