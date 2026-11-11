// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88016472;
  double density_weight = 0.38112451;
  double prefix_weight = 0.30088945;
  double neighborhood_weight = 0.04536355;
  double late_weight = 0.11498838;
  double critical_weight = 0.39341254;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
