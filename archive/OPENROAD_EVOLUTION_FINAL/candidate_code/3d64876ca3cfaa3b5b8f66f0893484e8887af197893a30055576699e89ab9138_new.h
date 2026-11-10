// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52588208;
  double density_weight = 0.58762145;
  double prefix_weight = 0.07293667;
  double neighborhood_weight = 0.26682963;
  double late_weight = 0.24245151;
  double critical_weight = 0.32103356;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
