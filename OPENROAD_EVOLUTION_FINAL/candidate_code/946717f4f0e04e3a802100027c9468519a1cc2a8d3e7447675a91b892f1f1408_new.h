// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59537279;
  double density_weight = 0.40493804;
  double prefix_weight = 0.15422137;
  double neighborhood_weight = 0.09717775;
  double late_weight = 0.25352189;
  double critical_weight = 0.42604424;
  unsigned budget = 39;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
