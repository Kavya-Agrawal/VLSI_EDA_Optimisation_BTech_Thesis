// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83285396;
  double density_weight = 0.28331364;
  double prefix_weight = 0.41858768;
  double neighborhood_weight = 0.00725867;
  double late_weight = 0.07150885;
  double critical_weight = 0.33420416;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
