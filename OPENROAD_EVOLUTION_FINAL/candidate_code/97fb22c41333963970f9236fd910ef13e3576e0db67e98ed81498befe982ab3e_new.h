// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83190350;
  double density_weight = 0.57508839;
  double prefix_weight = 0.06661874;
  double neighborhood_weight = 0.00958491;
  double late_weight = 0.04396039;
  double critical_weight = 0.37487848;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
