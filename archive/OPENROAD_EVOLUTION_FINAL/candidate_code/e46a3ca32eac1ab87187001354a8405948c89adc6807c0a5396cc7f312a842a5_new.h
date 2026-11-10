// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84702878;
  double density_weight = 0.08894657;
  double prefix_weight = 0.18148055;
  double neighborhood_weight = 0.21453969;
  double late_weight = 0.17338561;
  double critical_weight = 0.17903232;
  unsigned budget = 29;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
