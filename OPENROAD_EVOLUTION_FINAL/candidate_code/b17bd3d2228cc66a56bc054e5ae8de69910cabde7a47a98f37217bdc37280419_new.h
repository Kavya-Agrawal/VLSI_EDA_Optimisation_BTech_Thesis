// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66312572;
  double density_weight = 0.04649926;
  double prefix_weight = 0.11602780;
  double neighborhood_weight = 0.25832881;
  double late_weight = 0.16258076;
  double critical_weight = 0.03008183;
  unsigned budget = 26;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
