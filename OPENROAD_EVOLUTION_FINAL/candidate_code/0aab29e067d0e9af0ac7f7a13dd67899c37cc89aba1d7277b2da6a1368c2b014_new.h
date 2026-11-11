// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54120665;
  double density_weight = 0.22871342;
  double prefix_weight = 0.03782309;
  double neighborhood_weight = 0.03921945;
  double late_weight = 0.21335317;
  double critical_weight = 0.20215817;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
