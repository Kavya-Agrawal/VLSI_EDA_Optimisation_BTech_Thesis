// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06646762;
  double density_weight = 0.44942437;
  double prefix_weight = 0.48272794;
  double neighborhood_weight = 0.09819437;
  double late_weight = 0.08054126;
  double critical_weight = 0.00788444;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
