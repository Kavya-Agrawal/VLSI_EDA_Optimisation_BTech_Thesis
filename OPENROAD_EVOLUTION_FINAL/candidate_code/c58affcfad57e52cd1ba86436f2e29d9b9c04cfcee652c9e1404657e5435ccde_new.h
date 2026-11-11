// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47059548;
  double density_weight = 0.01067452;
  double prefix_weight = 0.19658521;
  double neighborhood_weight = 0.17780861;
  double late_weight = 0.19277429;
  double critical_weight = 0.04137362;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
