// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88927318;
  double density_weight = 0.17354910;
  double prefix_weight = 0.29322488;
  double neighborhood_weight = 0.36765720;
  double late_weight = 0.10816982;
  double critical_weight = 0.11056694;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
