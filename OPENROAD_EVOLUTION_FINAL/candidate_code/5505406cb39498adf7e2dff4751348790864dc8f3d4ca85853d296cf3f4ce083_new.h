// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73270333;
  double density_weight = 0.31332010;
  double prefix_weight = 0.03810786;
  double neighborhood_weight = 0.26646855;
  double late_weight = 0.29831938;
  double critical_weight = 0.41684436;
  unsigned budget = 7;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
