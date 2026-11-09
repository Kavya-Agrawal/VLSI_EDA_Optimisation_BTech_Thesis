// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07704096;
  double density_weight = 0.49488275;
  double prefix_weight = 0.37953054;
  double neighborhood_weight = 0.30088236;
  double late_weight = 0.28793618;
  double critical_weight = 0.21117611;
  unsigned budget = 38;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
