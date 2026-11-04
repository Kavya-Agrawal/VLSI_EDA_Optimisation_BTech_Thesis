// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65892041;
  double density_weight = 0.12913922;
  double prefix_weight = 0.09617048;
  double neighborhood_weight = 0.14743694;
  double late_weight = 0.22979883;
  double critical_weight = 0.15298999;
  unsigned budget = 24;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
