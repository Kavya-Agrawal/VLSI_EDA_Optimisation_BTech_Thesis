// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93134679;
  double density_weight = 0.47059948;
  double prefix_weight = 0.44242712;
  double neighborhood_weight = 0.09984981;
  double late_weight = 0.14981672;
  double critical_weight = 0.20394887;
  unsigned budget = 6;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
