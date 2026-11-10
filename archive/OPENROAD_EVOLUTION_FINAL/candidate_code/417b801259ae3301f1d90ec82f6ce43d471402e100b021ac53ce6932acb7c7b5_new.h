// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78014534;
  double density_weight = 0.30201501;
  double prefix_weight = 0.36015034;
  double neighborhood_weight = 0.01257175;
  double late_weight = 0.19203641;
  double critical_weight = 0.02558153;
  unsigned budget = 15;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
