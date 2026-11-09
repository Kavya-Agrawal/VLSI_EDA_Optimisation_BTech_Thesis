// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52404695;
  double density_weight = 0.58041842;
  double prefix_weight = 0.29800713;
  double neighborhood_weight = 0.26897403;
  double late_weight = 0.01203497;
  double critical_weight = 0.24938856;
  unsigned budget = 38;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
