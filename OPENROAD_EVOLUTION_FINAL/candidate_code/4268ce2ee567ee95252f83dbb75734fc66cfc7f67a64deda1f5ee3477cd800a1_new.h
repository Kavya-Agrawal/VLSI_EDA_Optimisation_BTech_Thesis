// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88390531;
  double density_weight = 0.23595573;
  double prefix_weight = 0.28800837;
  double neighborhood_weight = 0.21417336;
  double late_weight = 0.12442035;
  double critical_weight = 0.33067131;
  unsigned budget = 6;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
