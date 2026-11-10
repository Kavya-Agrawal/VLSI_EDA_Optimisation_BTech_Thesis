// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46732307;
  double density_weight = 0.33034795;
  double prefix_weight = 0.46727877;
  double neighborhood_weight = 0.16698549;
  double late_weight = 0.05658752;
  double critical_weight = 0.20968031;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
