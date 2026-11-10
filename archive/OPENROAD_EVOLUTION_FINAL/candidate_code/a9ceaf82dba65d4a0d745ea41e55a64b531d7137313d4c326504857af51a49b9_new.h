// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64134845;
  double density_weight = 0.51812684;
  double prefix_weight = 0.05474119;
  double neighborhood_weight = 0.03551343;
  double late_weight = 0.13643568;
  double critical_weight = 0.32841893;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
