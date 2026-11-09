// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42645615;
  double density_weight = 0.31699890;
  double prefix_weight = 0.38944868;
  double neighborhood_weight = 0.23735927;
  double late_weight = 0.08605236;
  double critical_weight = 0.05329841;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
