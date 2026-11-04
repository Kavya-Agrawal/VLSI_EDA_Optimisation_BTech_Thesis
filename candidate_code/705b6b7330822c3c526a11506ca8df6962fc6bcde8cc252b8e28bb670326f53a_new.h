// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31656009;
  double density_weight = 0.50194120;
  double prefix_weight = 0.23939651;
  double neighborhood_weight = 0.26715298;
  double late_weight = 0.19882160;
  double critical_weight = 0.42234222;
  unsigned budget = 29;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
