// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43364101;
  double density_weight = 0.13550300;
  double prefix_weight = 0.02002736;
  double neighborhood_weight = 0.05690817;
  double late_weight = 0.03179140;
  double critical_weight = 0.36232148;
  unsigned budget = 34;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
