// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72766414;
  double density_weight = 0.46071908;
  double prefix_weight = 0.22516574;
  double neighborhood_weight = 0.36642623;
  double late_weight = 0.11189594;
  double critical_weight = 0.06958856;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
