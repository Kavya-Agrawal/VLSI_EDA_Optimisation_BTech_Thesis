// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75777025;
  double density_weight = 0.37814022;
  double prefix_weight = 0.17857332;
  double neighborhood_weight = 0.05671448;
  double late_weight = 0.29403715;
  double critical_weight = 0.03826190;
  unsigned budget = 13;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
