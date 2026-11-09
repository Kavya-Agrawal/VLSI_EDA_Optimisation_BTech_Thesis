// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43969036;
  double density_weight = 0.28012627;
  double prefix_weight = 0.44803718;
  double neighborhood_weight = 0.01771142;
  double late_weight = 0.24491155;
  double critical_weight = 0.05975485;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
