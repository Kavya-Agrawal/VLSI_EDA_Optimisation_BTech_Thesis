// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72002480;
  double density_weight = 0.11210934;
  double prefix_weight = 0.34152729;
  double neighborhood_weight = 0.03641525;
  double late_weight = 0.28543035;
  double critical_weight = 0.27514151;
  unsigned budget = 25;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
