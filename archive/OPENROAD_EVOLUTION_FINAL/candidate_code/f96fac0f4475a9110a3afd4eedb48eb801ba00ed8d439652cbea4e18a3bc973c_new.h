// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98853269;
  double density_weight = 0.23054590;
  double prefix_weight = 0.11011312;
  double neighborhood_weight = 0.08914730;
  double late_weight = 0.26831421;
  double critical_weight = 0.39171725;
  unsigned budget = 21;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
