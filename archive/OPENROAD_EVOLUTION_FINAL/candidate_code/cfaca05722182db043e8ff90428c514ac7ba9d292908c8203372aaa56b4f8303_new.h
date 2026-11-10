// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75927983;
  double density_weight = 0.05359490;
  double prefix_weight = 0.41911675;
  double neighborhood_weight = 0.30680497;
  double late_weight = 0.17657903;
  double critical_weight = 0.40245148;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
