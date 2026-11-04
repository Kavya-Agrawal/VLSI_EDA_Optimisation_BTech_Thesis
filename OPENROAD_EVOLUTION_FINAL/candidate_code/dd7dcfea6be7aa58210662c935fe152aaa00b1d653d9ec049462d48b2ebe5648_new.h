// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78480257;
  double density_weight = 0.11038757;
  double prefix_weight = 0.31469119;
  double neighborhood_weight = 0.24189802;
  double late_weight = 0.19099064;
  double critical_weight = 0.08665051;
  unsigned budget = 21;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
