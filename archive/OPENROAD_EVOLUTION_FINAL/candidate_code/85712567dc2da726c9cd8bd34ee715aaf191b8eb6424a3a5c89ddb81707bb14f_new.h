// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72229070;
  double density_weight = 0.14172644;
  double prefix_weight = 0.23234380;
  double neighborhood_weight = 0.08637640;
  double late_weight = 0.06970695;
  double critical_weight = 0.47996676;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
