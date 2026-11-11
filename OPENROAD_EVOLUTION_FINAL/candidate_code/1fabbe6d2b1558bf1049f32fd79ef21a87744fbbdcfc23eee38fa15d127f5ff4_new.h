// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53348739;
  double density_weight = 0.41805036;
  double prefix_weight = 0.13539733;
  double neighborhood_weight = 0.09458371;
  double late_weight = 0.06598666;
  double critical_weight = 0.07083986;
  unsigned budget = 29;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
