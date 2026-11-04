// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25763099;
  double density_weight = 0.18189327;
  double prefix_weight = 0.18505938;
  double neighborhood_weight = 0.17999944;
  double late_weight = 0.07981265;
  double critical_weight = 0.20106094;
  unsigned budget = 17;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
