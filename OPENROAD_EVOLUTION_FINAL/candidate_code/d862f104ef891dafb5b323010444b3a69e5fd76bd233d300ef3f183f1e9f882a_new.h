// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89807684;
  double density_weight = 0.33162256;
  double prefix_weight = 0.09971848;
  double neighborhood_weight = 0.39302928;
  double late_weight = 0.04051321;
  double critical_weight = 0.24786880;
  unsigned budget = 9;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
