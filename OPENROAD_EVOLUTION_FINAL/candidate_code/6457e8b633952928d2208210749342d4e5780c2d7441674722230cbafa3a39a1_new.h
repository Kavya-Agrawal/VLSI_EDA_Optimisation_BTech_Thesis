// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80157253;
  double density_weight = 0.53211877;
  double prefix_weight = 0.46824193;
  double neighborhood_weight = 0.11116092;
  double late_weight = 0.15723092;
  double critical_weight = 0.32642494;
  unsigned budget = 14;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
