// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37137695;
  double density_weight = 0.28721012;
  double prefix_weight = 0.10168078;
  double neighborhood_weight = 0.05171252;
  double late_weight = 0.20105252;
  double critical_weight = 0.30413991;
  unsigned budget = 34;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
