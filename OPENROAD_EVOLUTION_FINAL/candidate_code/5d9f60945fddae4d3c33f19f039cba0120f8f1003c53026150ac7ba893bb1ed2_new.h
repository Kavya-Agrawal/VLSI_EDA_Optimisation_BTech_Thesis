// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12409556;
  double density_weight = 0.24238943;
  double prefix_weight = 0.45322202;
  double neighborhood_weight = 0.18662584;
  double late_weight = 0.17629567;
  double critical_weight = 0.44832587;
  unsigned budget = 34;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
