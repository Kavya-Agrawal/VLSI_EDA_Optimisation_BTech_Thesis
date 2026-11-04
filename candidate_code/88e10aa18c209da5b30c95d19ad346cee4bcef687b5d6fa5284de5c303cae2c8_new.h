// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02878309;
  double density_weight = 0.34775518;
  double prefix_weight = 0.08587793;
  double neighborhood_weight = 0.13946008;
  double late_weight = 0.23025068;
  double critical_weight = 0.19114561;
  unsigned budget = 33;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
