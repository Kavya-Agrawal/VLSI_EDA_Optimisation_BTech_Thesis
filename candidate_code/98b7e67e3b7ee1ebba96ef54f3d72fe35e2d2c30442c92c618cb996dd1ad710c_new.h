// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70033579;
  double density_weight = 0.01633986;
  double prefix_weight = 0.31331106;
  double neighborhood_weight = 0.12063114;
  double late_weight = 0.13032753;
  double critical_weight = 0.25997259;
  unsigned budget = 10;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
