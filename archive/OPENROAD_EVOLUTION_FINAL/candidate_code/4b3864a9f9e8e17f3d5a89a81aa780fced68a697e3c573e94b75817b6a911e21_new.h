// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99605768;
  double density_weight = 0.50568576;
  double prefix_weight = 0.17282685;
  double neighborhood_weight = 0.33721225;
  double late_weight = 0.15206374;
  double critical_weight = 0.42111594;
  unsigned budget = 35;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
