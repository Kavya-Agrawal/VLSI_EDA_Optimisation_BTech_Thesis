// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25432519;
  double density_weight = 0.40038194;
  double prefix_weight = 0.33288462;
  double neighborhood_weight = 0.38041780;
  double late_weight = 0.04610753;
  double critical_weight = 0.19544607;
  unsigned budget = 19;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
