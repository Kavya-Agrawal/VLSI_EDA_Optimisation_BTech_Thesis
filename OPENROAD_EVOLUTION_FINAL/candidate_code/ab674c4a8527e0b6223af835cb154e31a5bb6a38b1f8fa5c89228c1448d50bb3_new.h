// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03261576;
  double density_weight = 0.41462306;
  double prefix_weight = 0.30495327;
  double neighborhood_weight = 0.15587151;
  double late_weight = 0.03981959;
  double critical_weight = 0.01170163;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
