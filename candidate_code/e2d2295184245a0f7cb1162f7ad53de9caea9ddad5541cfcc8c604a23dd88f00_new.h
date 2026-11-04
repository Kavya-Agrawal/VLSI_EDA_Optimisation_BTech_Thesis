// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33839317;
  double density_weight = 0.47953012;
  double prefix_weight = 0.43245398;
  double neighborhood_weight = 0.25193644;
  double late_weight = 0.02519999;
  double critical_weight = 0.40846215;
  unsigned budget = 29;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
