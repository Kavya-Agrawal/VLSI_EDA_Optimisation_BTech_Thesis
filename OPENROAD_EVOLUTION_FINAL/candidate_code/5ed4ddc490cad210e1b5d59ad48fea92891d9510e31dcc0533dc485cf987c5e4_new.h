// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89288126;
  double density_weight = 0.00933989;
  double prefix_weight = 0.02800137;
  double neighborhood_weight = 0.31395594;
  double late_weight = 0.04960308;
  double critical_weight = 0.06948205;
  unsigned budget = 13;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
