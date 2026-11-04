// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87218464;
  double density_weight = 0.04140840;
  double prefix_weight = 0.33959973;
  double neighborhood_weight = 0.31453324;
  double late_weight = 0.15654308;
  double critical_weight = 0.35096883;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
