// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65247158;
  double density_weight = 0.22624502;
  double prefix_weight = 0.14779909;
  double neighborhood_weight = 0.19027130;
  double late_weight = 0.03575815;
  double critical_weight = 0.17209141;
  unsigned budget = 23;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
