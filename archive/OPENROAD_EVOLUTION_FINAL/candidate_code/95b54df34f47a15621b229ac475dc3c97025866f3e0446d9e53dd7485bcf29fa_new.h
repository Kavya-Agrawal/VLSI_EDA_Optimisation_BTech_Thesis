// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42306425;
  double density_weight = 0.13918907;
  double prefix_weight = 0.33886639;
  double neighborhood_weight = 0.39485994;
  double late_weight = 0.22755214;
  double critical_weight = 0.35586634;
  unsigned budget = 40;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
