// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71319406;
  double density_weight = 0.27333075;
  double prefix_weight = 0.34043008;
  double neighborhood_weight = 0.39265197;
  double late_weight = 0.12009456;
  double critical_weight = 0.06117076;
  unsigned budget = 6;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
