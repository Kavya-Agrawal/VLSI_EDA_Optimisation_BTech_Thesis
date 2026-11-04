// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82791301;
  double density_weight = 0.59907607;
  double prefix_weight = 0.27368002;
  double neighborhood_weight = 0.09536208;
  double late_weight = 0.07606276;
  double critical_weight = 0.29776981;
  unsigned budget = 4;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
