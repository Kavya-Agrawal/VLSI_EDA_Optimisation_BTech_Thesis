// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10648319;
  double density_weight = 0.20377241;
  double prefix_weight = 0.29973973;
  double neighborhood_weight = 0.01741599;
  double late_weight = 0.13219339;
  double critical_weight = 0.05360768;
  unsigned budget = 5;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
