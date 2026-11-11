// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04120923;
  double density_weight = 0.25919182;
  double prefix_weight = 0.41609030;
  double neighborhood_weight = 0.19300852;
  double late_weight = 0.08171886;
  double critical_weight = 0.24088850;
  unsigned budget = 12;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
