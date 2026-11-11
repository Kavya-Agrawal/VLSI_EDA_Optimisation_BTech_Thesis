// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96616481;
  double density_weight = 0.22357312;
  double prefix_weight = 0.09876324;
  double neighborhood_weight = 0.07532218;
  double late_weight = 0.02933713;
  double critical_weight = 0.06022097;
  unsigned budget = 24;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
