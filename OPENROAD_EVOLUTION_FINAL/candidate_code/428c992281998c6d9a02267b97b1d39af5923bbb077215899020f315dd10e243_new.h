// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78259657;
  double density_weight = 0.01882526;
  double prefix_weight = 0.16332849;
  double neighborhood_weight = 0.16528799;
  double late_weight = 0.13502991;
  double critical_weight = 0.03868657;
  unsigned budget = 13;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
