// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94909877;
  double density_weight = 0.52131621;
  double prefix_weight = 0.11282207;
  double neighborhood_weight = 0.39254218;
  double late_weight = 0.17000911;
  double critical_weight = 0.36337066;
  unsigned budget = 23;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
