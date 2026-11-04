// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34836989;
  double density_weight = 0.12353016;
  double prefix_weight = 0.20885963;
  double neighborhood_weight = 0.36058175;
  double late_weight = 0.02063244;
  double critical_weight = 0.09034093;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
