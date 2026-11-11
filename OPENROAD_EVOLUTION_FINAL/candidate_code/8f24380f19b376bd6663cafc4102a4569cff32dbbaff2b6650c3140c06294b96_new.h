// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31659831;
  double density_weight = 0.08242597;
  double prefix_weight = 0.43018977;
  double neighborhood_weight = 0.19403458;
  double late_weight = 0.18355412;
  double critical_weight = 0.31931312;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
