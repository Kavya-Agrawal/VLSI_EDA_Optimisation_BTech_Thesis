// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17430924;
  double density_weight = 0.30760892;
  double prefix_weight = 0.34254041;
  double neighborhood_weight = 0.39879450;
  double late_weight = 0.12093113;
  double critical_weight = 0.21621961;
  unsigned budget = 33;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
