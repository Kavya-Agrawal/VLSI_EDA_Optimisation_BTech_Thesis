// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16681285;
  double density_weight = 0.57090874;
  double prefix_weight = 0.17718327;
  double neighborhood_weight = 0.12352304;
  double late_weight = 0.27874416;
  double critical_weight = 0.37431988;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
