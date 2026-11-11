// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58416426;
  double density_weight = 0.42796075;
  double prefix_weight = 0.37169583;
  double neighborhood_weight = 0.08555811;
  double late_weight = 0.00328446;
  double critical_weight = 0.17757723;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
