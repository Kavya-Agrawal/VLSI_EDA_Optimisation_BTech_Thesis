// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34293894;
  double density_weight = 0.36398108;
  double prefix_weight = 0.20613238;
  double neighborhood_weight = 0.24312072;
  double late_weight = 0.28255023;
  double critical_weight = 0.23488063;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
