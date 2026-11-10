// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14219868;
  double density_weight = 0.40534267;
  double prefix_weight = 0.47639270;
  double neighborhood_weight = 0.38138056;
  double late_weight = 0.16814786;
  double critical_weight = 0.15530717;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
