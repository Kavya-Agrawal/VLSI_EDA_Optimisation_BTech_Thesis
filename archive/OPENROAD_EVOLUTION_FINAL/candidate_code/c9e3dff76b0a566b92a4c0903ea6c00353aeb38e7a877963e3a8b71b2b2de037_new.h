// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17591572;
  double density_weight = 0.59197995;
  double prefix_weight = 0.39658423;
  double neighborhood_weight = 0.25957952;
  double late_weight = 0.15799313;
  double critical_weight = 0.14440057;
  unsigned budget = 15;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
