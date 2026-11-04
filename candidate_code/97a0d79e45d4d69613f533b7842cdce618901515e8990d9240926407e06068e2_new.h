// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33350384;
  double density_weight = 0.53544310;
  double prefix_weight = 0.38022091;
  double neighborhood_weight = 0.19998624;
  double late_weight = 0.25712805;
  double critical_weight = 0.45133010;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
