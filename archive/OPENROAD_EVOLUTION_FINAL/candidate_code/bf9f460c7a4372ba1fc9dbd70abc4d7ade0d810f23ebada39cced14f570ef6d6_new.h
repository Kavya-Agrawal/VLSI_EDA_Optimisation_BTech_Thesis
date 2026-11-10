// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61557212;
  double density_weight = 0.59552539;
  double prefix_weight = 0.04802968;
  double neighborhood_weight = 0.37952513;
  double late_weight = 0.25636043;
  double critical_weight = 0.18824599;
  unsigned budget = 36;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
