// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20398300;
  double density_weight = 0.09418764;
  double prefix_weight = 0.40625090;
  double neighborhood_weight = 0.07871045;
  double late_weight = 0.22804355;
  double critical_weight = 0.01239826;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
