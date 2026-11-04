// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02966299;
  double density_weight = 0.04656276;
  double prefix_weight = 0.00613668;
  double neighborhood_weight = 0.00576971;
  double late_weight = 0.00540261;
  double critical_weight = 0.42601452;
  unsigned budget = 4;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
