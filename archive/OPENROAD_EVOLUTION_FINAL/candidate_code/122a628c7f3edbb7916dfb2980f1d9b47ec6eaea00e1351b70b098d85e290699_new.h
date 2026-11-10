// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15129250;
  double density_weight = 0.14360460;
  double prefix_weight = 0.35363500;
  double neighborhood_weight = 0.35249525;
  double late_weight = 0.15694443;
  double critical_weight = 0.14278568;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
