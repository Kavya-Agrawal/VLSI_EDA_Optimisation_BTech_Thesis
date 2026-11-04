// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41268062;
  double density_weight = 0.30507446;
  double prefix_weight = 0.15108641;
  double neighborhood_weight = 0.29659541;
  double late_weight = 0.16258210;
  double critical_weight = 0.19082938;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
