// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17211455;
  double density_weight = 0.54447053;
  double prefix_weight = 0.12063128;
  double neighborhood_weight = 0.27411402;
  double late_weight = 0.27891755;
  double critical_weight = 0.20132015;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
