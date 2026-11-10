// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08085848;
  double density_weight = 0.02195576;
  double prefix_weight = 0.01190767;
  double neighborhood_weight = 0.08325066;
  double late_weight = 0.20407309;
  double critical_weight = 0.12446874;
  unsigned budget = 13;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
