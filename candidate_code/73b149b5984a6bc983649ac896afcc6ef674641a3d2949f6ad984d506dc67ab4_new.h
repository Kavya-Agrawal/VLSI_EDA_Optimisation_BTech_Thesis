// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02091998;
  double density_weight = 0.11015097;
  double prefix_weight = 0.23766189;
  double neighborhood_weight = 0.11941512;
  double late_weight = 0.09295045;
  double critical_weight = 0.45644321;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
