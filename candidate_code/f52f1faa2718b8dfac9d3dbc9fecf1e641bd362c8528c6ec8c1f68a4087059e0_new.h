// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47068883;
  double density_weight = 0.23613834;
  double prefix_weight = 0.20321078;
  double neighborhood_weight = 0.27479310;
  double late_weight = 0.27249168;
  double critical_weight = 0.27418599;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
