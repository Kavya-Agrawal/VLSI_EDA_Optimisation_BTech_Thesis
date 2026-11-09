// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67538547;
  double density_weight = 0.25630158;
  double prefix_weight = 0.19125050;
  double neighborhood_weight = 0.15502039;
  double late_weight = 0.05682775;
  double critical_weight = 0.29989421;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
