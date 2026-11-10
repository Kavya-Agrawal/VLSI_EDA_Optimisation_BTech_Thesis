// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17627840;
  double density_weight = 0.29269028;
  double prefix_weight = 0.06311947;
  double neighborhood_weight = 0.05655871;
  double late_weight = 0.02854013;
  double critical_weight = 0.02415149;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
