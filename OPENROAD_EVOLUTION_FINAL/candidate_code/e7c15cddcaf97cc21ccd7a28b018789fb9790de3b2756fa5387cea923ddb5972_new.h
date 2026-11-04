// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86366628;
  double density_weight = 0.33192034;
  double prefix_weight = 0.04121532;
  double neighborhood_weight = 0.00146166;
  double late_weight = 0.16515626;
  double critical_weight = 0.10432777;
  unsigned budget = 6;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
