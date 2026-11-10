// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74565042;
  double density_weight = 0.44537306;
  double prefix_weight = 0.35620929;
  double neighborhood_weight = 0.01125615;
  double late_weight = 0.01875641;
  double critical_weight = 0.31533307;
  unsigned budget = 38;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
