// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64654840;
  double density_weight = 0.18721451;
  double prefix_weight = 0.30682243;
  double neighborhood_weight = 0.16221254;
  double late_weight = 0.16822945;
  double critical_weight = 0.47888054;
  unsigned budget = 31;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
