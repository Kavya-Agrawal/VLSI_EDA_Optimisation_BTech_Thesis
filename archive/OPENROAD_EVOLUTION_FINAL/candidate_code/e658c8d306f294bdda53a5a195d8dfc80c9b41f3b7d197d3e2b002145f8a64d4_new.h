// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44285640;
  double density_weight = 0.00404786;
  double prefix_weight = 0.03926603;
  double neighborhood_weight = 0.21829733;
  double late_weight = 0.03854296;
  double critical_weight = 0.25993884;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
