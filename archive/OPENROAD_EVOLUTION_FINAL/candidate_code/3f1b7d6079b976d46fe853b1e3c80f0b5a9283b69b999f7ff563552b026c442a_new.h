// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74349176;
  double density_weight = 0.45838236;
  double prefix_weight = 0.36279555;
  double neighborhood_weight = 0.01997055;
  double late_weight = 0.03823617;
  double critical_weight = 0.37831747;
  unsigned budget = 39;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
