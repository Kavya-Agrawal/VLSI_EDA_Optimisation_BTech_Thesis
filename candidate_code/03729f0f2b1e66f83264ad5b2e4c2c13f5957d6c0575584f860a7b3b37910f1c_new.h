// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83660685;
  double density_weight = 0.42550057;
  double prefix_weight = 0.43066998;
  double neighborhood_weight = 0.19039685;
  double late_weight = 0.25723181;
  double critical_weight = 0.12135516;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
