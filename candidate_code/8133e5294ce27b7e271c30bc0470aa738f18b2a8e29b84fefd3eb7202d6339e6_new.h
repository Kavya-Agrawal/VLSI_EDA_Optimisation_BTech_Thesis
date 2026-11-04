// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73056407;
  double density_weight = 0.04539307;
  double prefix_weight = 0.31360509;
  double neighborhood_weight = 0.24902426;
  double late_weight = 0.19853709;
  double critical_weight = 0.49150953;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
