// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41823184;
  double density_weight = 0.15121842;
  double prefix_weight = 0.11507196;
  double neighborhood_weight = 0.28323327;
  double late_weight = 0.14372470;
  double critical_weight = 0.06407049;
  unsigned budget = 13;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
