// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58020975;
  double density_weight = 0.39425309;
  double prefix_weight = 0.06642432;
  double neighborhood_weight = 0.31248661;
  double late_weight = 0.09469924;
  double critical_weight = 0.32965845;
  unsigned budget = 17;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
