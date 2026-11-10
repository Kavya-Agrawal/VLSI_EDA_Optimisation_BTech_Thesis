// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00806186;
  double density_weight = 0.33082782;
  double prefix_weight = 0.09059667;
  double neighborhood_weight = 0.13570510;
  double late_weight = 0.09387982;
  double critical_weight = 0.05865505;
  unsigned budget = 9;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
