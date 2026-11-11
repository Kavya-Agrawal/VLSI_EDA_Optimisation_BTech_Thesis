// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05444494;
  double density_weight = 0.56139235;
  double prefix_weight = 0.33290314;
  double neighborhood_weight = 0.00426603;
  double late_weight = 0.13901661;
  double critical_weight = 0.33735080;
  unsigned budget = 29;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
