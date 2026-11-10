// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34677712;
  double density_weight = 0.36559268;
  double prefix_weight = 0.03447497;
  double neighborhood_weight = 0.29782934;
  double late_weight = 0.23638669;
  double critical_weight = 0.37440021;
  unsigned budget = 35;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
