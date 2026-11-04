// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57814704;
  double density_weight = 0.35001340;
  double prefix_weight = 0.20628278;
  double neighborhood_weight = 0.36992044;
  double late_weight = 0.00813079;
  double critical_weight = 0.44808735;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
