// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19353468;
  double density_weight = 0.26435575;
  double prefix_weight = 0.29962463;
  double neighborhood_weight = 0.35138474;
  double late_weight = 0.09478304;
  double critical_weight = 0.11198642;
  unsigned budget = 14;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
