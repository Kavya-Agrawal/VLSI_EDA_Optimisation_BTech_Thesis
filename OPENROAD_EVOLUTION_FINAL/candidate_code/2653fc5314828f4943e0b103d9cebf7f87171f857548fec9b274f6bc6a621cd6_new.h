// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70405491;
  double density_weight = 0.38609350;
  double prefix_weight = 0.05751439;
  double neighborhood_weight = 0.20029607;
  double late_weight = 0.08841290;
  double critical_weight = 0.40270859;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
