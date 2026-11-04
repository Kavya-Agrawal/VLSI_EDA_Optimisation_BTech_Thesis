// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48021344;
  double density_weight = 0.40764046;
  double prefix_weight = 0.17647541;
  double neighborhood_weight = 0.07171083;
  double late_weight = 0.28667109;
  double critical_weight = 0.49174065;
  unsigned budget = 13;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
