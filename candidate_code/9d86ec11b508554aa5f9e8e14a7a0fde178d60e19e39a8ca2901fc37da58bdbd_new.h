// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56374136;
  double density_weight = 0.43245694;
  double prefix_weight = 0.33313605;
  double neighborhood_weight = 0.27914419;
  double late_weight = 0.10543276;
  double critical_weight = 0.43338985;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
