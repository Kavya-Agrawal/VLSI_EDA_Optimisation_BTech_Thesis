// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23133926;
  double density_weight = 0.24510745;
  double prefix_weight = 0.19699186;
  double neighborhood_weight = 0.31745623;
  double late_weight = 0.13051806;
  double critical_weight = 0.29227089;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
