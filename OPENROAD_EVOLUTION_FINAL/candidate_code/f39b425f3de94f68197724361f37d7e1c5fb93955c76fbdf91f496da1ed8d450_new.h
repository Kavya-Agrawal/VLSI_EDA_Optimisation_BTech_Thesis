// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60446378;
  double density_weight = 0.25785778;
  double prefix_weight = 0.25993559;
  double neighborhood_weight = 0.09765121;
  double late_weight = 0.17401168;
  double critical_weight = 0.22218053;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
