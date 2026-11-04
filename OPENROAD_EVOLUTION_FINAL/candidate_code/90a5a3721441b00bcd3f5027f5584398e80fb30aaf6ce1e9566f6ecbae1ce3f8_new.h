// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16451503;
  double density_weight = 0.06824692;
  double prefix_weight = 0.36192469;
  double neighborhood_weight = 0.26085231;
  double late_weight = 0.01419998;
  double critical_weight = 0.43449512;
  unsigned budget = 5;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
