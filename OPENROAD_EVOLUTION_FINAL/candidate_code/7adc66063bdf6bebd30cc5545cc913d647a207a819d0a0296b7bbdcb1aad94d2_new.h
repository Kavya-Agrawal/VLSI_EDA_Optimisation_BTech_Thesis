// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90328782;
  double density_weight = 0.52129430;
  double prefix_weight = 0.35341972;
  double neighborhood_weight = 0.31977676;
  double late_weight = 0.27003890;
  double critical_weight = 0.01109023;
  unsigned budget = 39;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
