// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33109851;
  double density_weight = 0.20595947;
  double prefix_weight = 0.15735533;
  double neighborhood_weight = 0.18780277;
  double late_weight = 0.04565462;
  double critical_weight = 0.25887570;
  unsigned budget = 5;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
