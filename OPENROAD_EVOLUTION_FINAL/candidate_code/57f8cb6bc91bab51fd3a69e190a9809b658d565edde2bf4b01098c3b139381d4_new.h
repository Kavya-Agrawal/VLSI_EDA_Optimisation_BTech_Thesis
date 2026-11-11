// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58092161;
  double density_weight = 0.41238263;
  double prefix_weight = 0.18647956;
  double neighborhood_weight = 0.32973715;
  double late_weight = 0.03271667;
  double critical_weight = 0.16907621;
  unsigned budget = 31;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
