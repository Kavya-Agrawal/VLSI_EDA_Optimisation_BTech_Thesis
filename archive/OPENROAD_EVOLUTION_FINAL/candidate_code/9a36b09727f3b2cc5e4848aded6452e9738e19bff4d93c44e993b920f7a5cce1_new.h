// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67131498;
  double density_weight = 0.51971473;
  double prefix_weight = 0.16701926;
  double neighborhood_weight = 0.28784386;
  double late_weight = 0.05419609;
  double critical_weight = 0.31630937;
  unsigned budget = 4;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
