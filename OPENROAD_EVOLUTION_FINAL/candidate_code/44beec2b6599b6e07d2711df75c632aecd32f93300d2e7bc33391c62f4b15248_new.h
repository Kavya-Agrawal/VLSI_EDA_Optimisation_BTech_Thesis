// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68275142;
  double density_weight = 0.57673889;
  double prefix_weight = 0.35850814;
  double neighborhood_weight = 0.36152478;
  double late_weight = 0.08329453;
  double critical_weight = 0.01839828;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
