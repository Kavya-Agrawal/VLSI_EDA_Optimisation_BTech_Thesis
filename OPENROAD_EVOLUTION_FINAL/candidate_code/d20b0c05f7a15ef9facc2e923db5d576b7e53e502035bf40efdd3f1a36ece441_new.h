// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41493080;
  double density_weight = 0.43366011;
  double prefix_weight = 0.25477163;
  double neighborhood_weight = 0.09838526;
  double late_weight = 0.28897090;
  double critical_weight = 0.04396385;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
