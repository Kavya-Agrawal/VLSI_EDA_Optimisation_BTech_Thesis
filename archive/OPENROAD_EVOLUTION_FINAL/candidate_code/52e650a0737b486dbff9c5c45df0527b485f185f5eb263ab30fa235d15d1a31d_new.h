// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78842015;
  double density_weight = 0.47560389;
  double prefix_weight = 0.43213476;
  double neighborhood_weight = 0.11521659;
  double late_weight = 0.17541287;
  double critical_weight = 0.02501138;
  unsigned budget = 38;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
