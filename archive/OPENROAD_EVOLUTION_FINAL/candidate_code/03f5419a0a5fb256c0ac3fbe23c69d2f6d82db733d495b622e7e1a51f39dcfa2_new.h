// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62487945;
  double density_weight = 0.03565012;
  double prefix_weight = 0.39703163;
  double neighborhood_weight = 0.12655406;
  double late_weight = 0.15391653;
  double critical_weight = 0.03094729;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
