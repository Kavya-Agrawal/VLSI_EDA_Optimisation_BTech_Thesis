// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49632109;
  double density_weight = 0.45064749;
  double prefix_weight = 0.45070411;
  double neighborhood_weight = 0.30372383;
  double late_weight = 0.16006706;
  double critical_weight = 0.20117014;
  unsigned budget = 27;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
