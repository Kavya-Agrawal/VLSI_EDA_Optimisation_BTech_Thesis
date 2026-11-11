// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73830169;
  double density_weight = 0.14568917;
  double prefix_weight = 0.07748058;
  double neighborhood_weight = 0.07203170;
  double late_weight = 0.11637333;
  double critical_weight = 0.14550745;
  unsigned budget = 5;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
