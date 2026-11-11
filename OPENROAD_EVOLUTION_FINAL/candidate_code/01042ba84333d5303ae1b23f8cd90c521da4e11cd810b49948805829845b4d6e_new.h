// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97895488;
  double density_weight = 0.45968498;
  double prefix_weight = 0.15168081;
  double neighborhood_weight = 0.03182239;
  double late_weight = 0.00266279;
  double critical_weight = 0.32256141;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
