// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36414425;
  double density_weight = 0.53320388;
  double prefix_weight = 0.39774585;
  double neighborhood_weight = 0.31093217;
  double late_weight = 0.13212340;
  double critical_weight = 0.18884803;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
