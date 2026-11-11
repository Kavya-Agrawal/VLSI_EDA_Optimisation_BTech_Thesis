// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64755382;
  double density_weight = 0.19215831;
  double prefix_weight = 0.43227720;
  double neighborhood_weight = 0.38860083;
  double late_weight = 0.10947535;
  double critical_weight = 0.00702427;
  unsigned budget = 19;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
