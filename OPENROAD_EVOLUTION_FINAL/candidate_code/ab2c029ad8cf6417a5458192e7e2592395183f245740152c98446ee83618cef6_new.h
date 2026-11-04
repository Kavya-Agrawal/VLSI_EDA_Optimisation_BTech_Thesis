// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23063362;
  double density_weight = 0.11295714;
  double prefix_weight = 0.08463890;
  double neighborhood_weight = 0.34341777;
  double late_weight = 0.10760943;
  double critical_weight = 0.25402669;
  unsigned budget = 7;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
