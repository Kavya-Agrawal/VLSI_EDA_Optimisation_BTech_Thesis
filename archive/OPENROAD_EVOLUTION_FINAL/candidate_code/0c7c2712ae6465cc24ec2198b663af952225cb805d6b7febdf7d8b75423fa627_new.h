// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29251420;
  double density_weight = 0.29666069;
  double prefix_weight = 0.13641959;
  double neighborhood_weight = 0.05951981;
  double late_weight = 0.22645946;
  double critical_weight = 0.21076131;
  unsigned budget = 35;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
