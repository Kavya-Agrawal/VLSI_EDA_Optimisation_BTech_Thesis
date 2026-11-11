// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79598494;
  double density_weight = 0.42386287;
  double prefix_weight = 0.07851167;
  double neighborhood_weight = 0.07388755;
  double late_weight = 0.21630489;
  double critical_weight = 0.27906375;
  unsigned budget = 12;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
