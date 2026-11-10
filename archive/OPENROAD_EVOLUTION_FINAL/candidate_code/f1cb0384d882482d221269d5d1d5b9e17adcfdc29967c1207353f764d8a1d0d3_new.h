// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03490999;
  double density_weight = 0.21160795;
  double prefix_weight = 0.04787832;
  double neighborhood_weight = 0.09096924;
  double late_weight = 0.25420708;
  double critical_weight = 0.07176024;
  unsigned budget = 29;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
