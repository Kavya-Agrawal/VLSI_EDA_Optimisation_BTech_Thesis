// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18683905;
  double density_weight = 0.31370213;
  double prefix_weight = 0.18394359;
  double neighborhood_weight = 0.13374524;
  double late_weight = 0.01245217;
  double critical_weight = 0.25133709;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
