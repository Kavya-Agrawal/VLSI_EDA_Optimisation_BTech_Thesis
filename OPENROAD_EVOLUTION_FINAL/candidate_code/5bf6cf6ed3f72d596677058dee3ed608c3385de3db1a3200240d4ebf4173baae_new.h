// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92590998;
  double density_weight = 0.26285183;
  double prefix_weight = 0.17328526;
  double neighborhood_weight = 0.26880417;
  double late_weight = 0.10067524;
  double critical_weight = 0.07542656;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
