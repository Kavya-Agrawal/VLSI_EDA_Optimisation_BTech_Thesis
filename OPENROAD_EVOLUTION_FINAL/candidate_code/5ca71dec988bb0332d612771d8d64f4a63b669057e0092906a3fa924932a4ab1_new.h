// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70155908;
  double density_weight = 0.15209530;
  double prefix_weight = 0.17413881;
  double neighborhood_weight = 0.12029483;
  double late_weight = 0.09179999;
  double critical_weight = 0.25205677;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
