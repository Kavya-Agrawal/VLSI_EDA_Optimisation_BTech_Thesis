// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11838257;
  double density_weight = 0.40467151;
  double prefix_weight = 0.07832059;
  double neighborhood_weight = 0.36592784;
  double late_weight = 0.07277755;
  double critical_weight = 0.12373450;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
