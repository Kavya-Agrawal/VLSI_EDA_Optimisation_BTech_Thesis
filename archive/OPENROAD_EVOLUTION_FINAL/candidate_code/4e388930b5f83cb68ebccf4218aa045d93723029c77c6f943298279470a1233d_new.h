// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71873354;
  double density_weight = 0.27625358;
  double prefix_weight = 0.39470810;
  double neighborhood_weight = 0.06576518;
  double late_weight = 0.24060455;
  double critical_weight = 0.46457883;
  unsigned budget = 4;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
