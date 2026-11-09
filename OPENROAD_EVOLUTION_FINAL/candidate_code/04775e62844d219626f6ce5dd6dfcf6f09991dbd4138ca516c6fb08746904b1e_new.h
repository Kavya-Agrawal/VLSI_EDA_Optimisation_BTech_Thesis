// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88732342;
  double density_weight = 0.01675315;
  double prefix_weight = 0.07379322;
  double neighborhood_weight = 0.37905133;
  double late_weight = 0.29861118;
  double critical_weight = 0.25390192;
  unsigned budget = 19;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
