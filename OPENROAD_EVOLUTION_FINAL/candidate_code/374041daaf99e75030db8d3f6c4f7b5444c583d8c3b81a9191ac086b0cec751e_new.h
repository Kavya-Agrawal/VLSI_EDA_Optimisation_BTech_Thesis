// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18294379;
  double density_weight = 0.33077378;
  double prefix_weight = 0.17679841;
  double neighborhood_weight = 0.32081022;
  double late_weight = 0.06624460;
  double critical_weight = 0.03256203;
  unsigned budget = 15;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
