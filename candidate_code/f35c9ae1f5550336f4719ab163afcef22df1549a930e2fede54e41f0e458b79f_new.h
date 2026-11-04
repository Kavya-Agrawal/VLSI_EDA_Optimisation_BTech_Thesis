// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73071862;
  double density_weight = 0.51185518;
  double prefix_weight = 0.42098838;
  double neighborhood_weight = 0.04092354;
  double late_weight = 0.17110351;
  double critical_weight = 0.45666903;
  unsigned budget = 18;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
