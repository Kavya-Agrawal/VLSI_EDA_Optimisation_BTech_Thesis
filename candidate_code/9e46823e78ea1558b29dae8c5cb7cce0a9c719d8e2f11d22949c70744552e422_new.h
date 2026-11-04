// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20740864;
  double density_weight = 0.21459591;
  double prefix_weight = 0.20591436;
  double neighborhood_weight = 0.16424268;
  double late_weight = 0.19845839;
  double critical_weight = 0.05315532;
  unsigned budget = 9;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
