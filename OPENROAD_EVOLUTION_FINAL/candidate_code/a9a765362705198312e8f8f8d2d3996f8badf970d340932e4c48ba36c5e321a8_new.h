// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92321157;
  double density_weight = 0.52185173;
  double prefix_weight = 0.12879049;
  double neighborhood_weight = 0.33895526;
  double late_weight = 0.25251652;
  double critical_weight = 0.01970986;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
