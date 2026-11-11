// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32094842;
  double density_weight = 0.47874236;
  double prefix_weight = 0.21315899;
  double neighborhood_weight = 0.23085913;
  double late_weight = 0.06566873;
  double critical_weight = 0.06209718;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
