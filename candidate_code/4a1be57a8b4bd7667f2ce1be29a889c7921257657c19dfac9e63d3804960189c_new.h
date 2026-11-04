// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97020778;
  double density_weight = 0.55462867;
  double prefix_weight = 0.15228210;
  double neighborhood_weight = 0.22745482;
  double late_weight = 0.09607852;
  double critical_weight = 0.08196525;
  unsigned budget = 19;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
