// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21980571;
  double density_weight = 0.13105201;
  double prefix_weight = 0.32197283;
  double neighborhood_weight = 0.00804870;
  double late_weight = 0.24040641;
  double critical_weight = 0.17886059;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
