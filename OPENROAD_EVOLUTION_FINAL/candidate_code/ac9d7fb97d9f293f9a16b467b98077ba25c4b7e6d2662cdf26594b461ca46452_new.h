// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70122650;
  double density_weight = 0.44618770;
  double prefix_weight = 0.06348203;
  double neighborhood_weight = 0.06705904;
  double late_weight = 0.22298502;
  double critical_weight = 0.26193469;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
