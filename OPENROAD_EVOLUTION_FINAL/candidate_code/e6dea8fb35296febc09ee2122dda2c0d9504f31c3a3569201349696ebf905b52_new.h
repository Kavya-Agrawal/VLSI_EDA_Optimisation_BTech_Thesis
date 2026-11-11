// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35821844;
  double density_weight = 0.53480625;
  double prefix_weight = 0.23332047;
  double neighborhood_weight = 0.27334615;
  double late_weight = 0.13474970;
  double critical_weight = 0.02495179;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
