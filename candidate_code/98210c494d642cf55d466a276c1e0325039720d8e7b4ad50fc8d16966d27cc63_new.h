// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01540905;
  double density_weight = 0.27129289;
  double prefix_weight = 0.05801054;
  double neighborhood_weight = 0.02730181;
  double late_weight = 0.13505000;
  double critical_weight = 0.46493777;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
