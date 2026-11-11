// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21621415;
  double density_weight = 0.20350928;
  double prefix_weight = 0.05534557;
  double neighborhood_weight = 0.15104265;
  double late_weight = 0.14419940;
  double critical_weight = 0.28721012;
  unsigned budget = 37;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
