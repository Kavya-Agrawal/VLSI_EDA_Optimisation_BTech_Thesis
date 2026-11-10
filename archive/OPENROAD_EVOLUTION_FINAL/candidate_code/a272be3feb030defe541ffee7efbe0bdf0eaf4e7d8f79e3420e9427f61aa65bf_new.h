// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05104734;
  double density_weight = 0.38228408;
  double prefix_weight = 0.12171959;
  double neighborhood_weight = 0.08200154;
  double late_weight = 0.23012576;
  double critical_weight = 0.08282202;
  unsigned budget = 38;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
