// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26473376;
  double density_weight = 0.23887150;
  double prefix_weight = 0.32219014;
  double neighborhood_weight = 0.31663253;
  double late_weight = 0.16934833;
  double critical_weight = 0.18093682;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
