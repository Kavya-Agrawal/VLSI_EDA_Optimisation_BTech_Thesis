// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99518583;
  double density_weight = 0.41593524;
  double prefix_weight = 0.09520755;
  double neighborhood_weight = 0.08412787;
  double late_weight = 0.24527664;
  double critical_weight = 0.10400195;
  unsigned budget = 19;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
