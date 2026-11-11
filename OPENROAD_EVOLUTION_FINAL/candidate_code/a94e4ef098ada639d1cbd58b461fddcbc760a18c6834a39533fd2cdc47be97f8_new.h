// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51648863;
  double density_weight = 0.15520307;
  double prefix_weight = 0.25673990;
  double neighborhood_weight = 0.19760663;
  double late_weight = 0.28632332;
  double critical_weight = 0.08084414;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
