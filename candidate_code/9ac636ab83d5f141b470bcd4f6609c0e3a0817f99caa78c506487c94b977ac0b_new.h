// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21875584;
  double density_weight = 0.06446829;
  double prefix_weight = 0.24961909;
  double neighborhood_weight = 0.00839147;
  double late_weight = 0.17448315;
  double critical_weight = 0.22821931;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
