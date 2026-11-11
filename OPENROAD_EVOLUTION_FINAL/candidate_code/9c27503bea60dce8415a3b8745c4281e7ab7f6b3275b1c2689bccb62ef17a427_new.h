// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29999131;
  double density_weight = 0.27109428;
  double prefix_weight = 0.24976972;
  double neighborhood_weight = 0.31091807;
  double late_weight = 0.19182589;
  double critical_weight = 0.07008775;
  unsigned budget = 14;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
