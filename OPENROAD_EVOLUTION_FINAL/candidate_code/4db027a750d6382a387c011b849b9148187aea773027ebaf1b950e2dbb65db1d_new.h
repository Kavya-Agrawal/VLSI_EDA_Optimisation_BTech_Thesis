// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46366054;
  double density_weight = 0.55259599;
  double prefix_weight = 0.48099523;
  double neighborhood_weight = 0.33090353;
  double late_weight = 0.25131026;
  double critical_weight = 0.43504435;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
