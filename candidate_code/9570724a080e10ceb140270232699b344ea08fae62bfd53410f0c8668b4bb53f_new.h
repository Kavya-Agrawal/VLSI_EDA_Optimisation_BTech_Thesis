// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00964282;
  double density_weight = 0.42361576;
  double prefix_weight = 0.36424418;
  double neighborhood_weight = 0.28311443;
  double late_weight = 0.05420489;
  double critical_weight = 0.06931185;
  unsigned budget = 33;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
