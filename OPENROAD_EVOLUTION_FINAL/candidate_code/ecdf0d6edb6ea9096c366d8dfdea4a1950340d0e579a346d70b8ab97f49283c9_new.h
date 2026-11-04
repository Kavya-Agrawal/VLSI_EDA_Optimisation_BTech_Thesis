// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08323326;
  double density_weight = 0.53075347;
  double prefix_weight = 0.05455970;
  double neighborhood_weight = 0.00583950;
  double late_weight = 0.23533482;
  double critical_weight = 0.36692221;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
