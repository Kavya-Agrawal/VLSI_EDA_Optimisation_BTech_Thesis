// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96708201;
  double density_weight = 0.42482985;
  double prefix_weight = 0.12177120;
  double neighborhood_weight = 0.27555040;
  double late_weight = 0.21676643;
  double critical_weight = 0.40752909;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
