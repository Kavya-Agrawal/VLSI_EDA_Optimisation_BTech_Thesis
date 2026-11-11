// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32776417;
  double density_weight = 0.19136939;
  double prefix_weight = 0.18713458;
  double neighborhood_weight = 0.34229227;
  double late_weight = 0.00968193;
  double critical_weight = 0.34717674;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
