// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87980333;
  double density_weight = 0.49219626;
  double prefix_weight = 0.14779856;
  double neighborhood_weight = 0.05969629;
  double late_weight = 0.07359319;
  double critical_weight = 0.03383042;
  unsigned budget = 25;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
