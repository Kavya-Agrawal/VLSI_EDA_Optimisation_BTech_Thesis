// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38647431;
  double density_weight = 0.23965595;
  double prefix_weight = 0.32053333;
  double neighborhood_weight = 0.25904692;
  double late_weight = 0.15071165;
  double critical_weight = 0.23174541;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
