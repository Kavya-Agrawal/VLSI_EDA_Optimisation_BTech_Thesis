// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85812309;
  double density_weight = 0.41759965;
  double prefix_weight = 0.03275840;
  double neighborhood_weight = 0.27731028;
  double late_weight = 0.05923068;
  double critical_weight = 0.34225893;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
