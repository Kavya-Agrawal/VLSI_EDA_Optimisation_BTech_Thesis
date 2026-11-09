// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71460938;
  double density_weight = 0.35973454;
  double prefix_weight = 0.37784017;
  double neighborhood_weight = 0.39815146;
  double late_weight = 0.18290020;
  double critical_weight = 0.33372862;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
