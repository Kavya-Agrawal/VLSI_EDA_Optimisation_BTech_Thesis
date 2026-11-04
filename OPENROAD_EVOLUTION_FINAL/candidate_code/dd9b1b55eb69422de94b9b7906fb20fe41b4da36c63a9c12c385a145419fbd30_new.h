// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33821738;
  double density_weight = 0.39373468;
  double prefix_weight = 0.27214964;
  double neighborhood_weight = 0.30666334;
  double late_weight = 0.05108811;
  double critical_weight = 0.11107895;
  unsigned budget = 24;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
