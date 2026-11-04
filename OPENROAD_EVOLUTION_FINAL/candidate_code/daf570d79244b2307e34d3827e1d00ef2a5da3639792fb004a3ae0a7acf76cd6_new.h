// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22332049;
  double density_weight = 0.18021031;
  double prefix_weight = 0.10281012;
  double neighborhood_weight = 0.31115309;
  double late_weight = 0.29412551;
  double critical_weight = 0.42387038;
  unsigned budget = 33;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
