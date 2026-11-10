// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45073369;
  double density_weight = 0.11629432;
  double prefix_weight = 0.12241909;
  double neighborhood_weight = 0.33813591;
  double late_weight = 0.26058975;
  double critical_weight = 0.34367362;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
