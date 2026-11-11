// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22633237;
  double density_weight = 0.47065651;
  double prefix_weight = 0.07480283;
  double neighborhood_weight = 0.08171010;
  double late_weight = 0.02024332;
  double critical_weight = 0.24569258;
  unsigned budget = 5;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
