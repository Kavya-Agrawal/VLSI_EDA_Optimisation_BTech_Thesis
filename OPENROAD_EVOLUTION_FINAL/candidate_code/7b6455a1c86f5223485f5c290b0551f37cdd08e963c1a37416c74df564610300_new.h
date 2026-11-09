// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25436111;
  double density_weight = 0.55457190;
  double prefix_weight = 0.48863871;
  double neighborhood_weight = 0.09212202;
  double late_weight = 0.01385250;
  double critical_weight = 0.28238546;
  unsigned budget = 18;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
