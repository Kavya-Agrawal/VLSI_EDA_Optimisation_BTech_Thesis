// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14545480;
  double density_weight = 0.04875791;
  double prefix_weight = 0.42937695;
  double neighborhood_weight = 0.09355441;
  double late_weight = 0.02692821;
  double critical_weight = 0.02575060;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
