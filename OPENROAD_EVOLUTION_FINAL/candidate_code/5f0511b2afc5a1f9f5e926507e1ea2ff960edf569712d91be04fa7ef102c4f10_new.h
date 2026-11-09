// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84793508;
  double density_weight = 0.54631513;
  double prefix_weight = 0.46341376;
  double neighborhood_weight = 0.23032744;
  double late_weight = 0.19738328;
  double critical_weight = 0.44334510;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
