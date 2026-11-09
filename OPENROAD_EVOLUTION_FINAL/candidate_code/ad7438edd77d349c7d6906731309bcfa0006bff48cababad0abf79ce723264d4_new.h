// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01547900;
  double density_weight = 0.19413857;
  double prefix_weight = 0.23406577;
  double neighborhood_weight = 0.18800010;
  double late_weight = 0.17109830;
  double critical_weight = 0.40623948;
  unsigned budget = 7;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
