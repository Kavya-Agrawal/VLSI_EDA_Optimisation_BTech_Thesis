// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71372104;
  double density_weight = 0.47120940;
  double prefix_weight = 0.35157679;
  double neighborhood_weight = 0.38397194;
  double late_weight = 0.15675701;
  double critical_weight = 0.03632677;
  unsigned budget = 26;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
