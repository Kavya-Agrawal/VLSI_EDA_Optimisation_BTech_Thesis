// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20901678;
  double density_weight = 0.34314597;
  double prefix_weight = 0.33715355;
  double neighborhood_weight = 0.02937032;
  double late_weight = 0.27984008;
  double critical_weight = 0.31242593;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
