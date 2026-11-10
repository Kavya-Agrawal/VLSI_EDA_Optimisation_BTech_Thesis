// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42683295;
  double density_weight = 0.40625773;
  double prefix_weight = 0.01767990;
  double neighborhood_weight = 0.05481085;
  double late_weight = 0.19152337;
  double critical_weight = 0.02164084;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
