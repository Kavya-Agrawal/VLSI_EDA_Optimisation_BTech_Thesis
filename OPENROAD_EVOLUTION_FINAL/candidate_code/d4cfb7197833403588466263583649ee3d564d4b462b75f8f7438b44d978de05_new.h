// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51203356;
  double density_weight = 0.23281603;
  double prefix_weight = 0.40272054;
  double neighborhood_weight = 0.22586268;
  double late_weight = 0.25506437;
  double critical_weight = 0.05337733;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
