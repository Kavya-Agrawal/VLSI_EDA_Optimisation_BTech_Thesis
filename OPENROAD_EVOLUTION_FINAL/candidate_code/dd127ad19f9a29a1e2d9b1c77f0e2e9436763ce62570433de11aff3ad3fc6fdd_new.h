// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24519892;
  double density_weight = 0.25669616;
  double prefix_weight = 0.05623309;
  double neighborhood_weight = 0.12579878;
  double late_weight = 0.16296654;
  double critical_weight = 0.42352778;
  unsigned budget = 4;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
