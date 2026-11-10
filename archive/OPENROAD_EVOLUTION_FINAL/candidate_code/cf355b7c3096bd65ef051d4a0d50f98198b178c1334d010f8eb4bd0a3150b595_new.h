// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56219809;
  double density_weight = 0.41928694;
  double prefix_weight = 0.01203686;
  double neighborhood_weight = 0.14352356;
  double late_weight = 0.21067187;
  double critical_weight = 0.08311159;
  unsigned budget = 11;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
