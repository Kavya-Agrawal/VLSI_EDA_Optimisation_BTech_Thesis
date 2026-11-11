// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26488912;
  double density_weight = 0.45344803;
  double prefix_weight = 0.25636825;
  double neighborhood_weight = 0.13734341;
  double late_weight = 0.22053839;
  double critical_weight = 0.37061915;
  unsigned budget = 29;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
