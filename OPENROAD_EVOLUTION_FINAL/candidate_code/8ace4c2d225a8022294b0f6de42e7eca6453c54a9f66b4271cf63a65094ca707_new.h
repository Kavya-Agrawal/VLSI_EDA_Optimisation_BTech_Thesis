// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34125726;
  double density_weight = 0.33475697;
  double prefix_weight = 0.47408717;
  double neighborhood_weight = 0.28571563;
  double late_weight = 0.11589763;
  double critical_weight = 0.18304389;
  unsigned budget = 30;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
