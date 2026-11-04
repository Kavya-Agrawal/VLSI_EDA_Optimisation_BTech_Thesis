// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30349680;
  double density_weight = 0.12417354;
  double prefix_weight = 0.20746857;
  double neighborhood_weight = 0.09612521;
  double late_weight = 0.16327677;
  double critical_weight = 0.26071439;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
