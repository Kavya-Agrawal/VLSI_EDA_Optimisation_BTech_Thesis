// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94636708;
  double density_weight = 0.35869110;
  double prefix_weight = 0.21993618;
  double neighborhood_weight = 0.33899611;
  double late_weight = 0.25693072;
  double critical_weight = 0.44776879;
  unsigned budget = 17;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
