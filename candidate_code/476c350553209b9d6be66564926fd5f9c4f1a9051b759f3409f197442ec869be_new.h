// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65817227;
  double density_weight = 0.58959414;
  double prefix_weight = 0.13084456;
  double neighborhood_weight = 0.21119055;
  double late_weight = 0.27313548;
  double critical_weight = 0.22317261;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
