// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47471963;
  double density_weight = 0.24536530;
  double prefix_weight = 0.28626063;
  double neighborhood_weight = 0.32991540;
  double late_weight = 0.18887298;
  double critical_weight = 0.00768963;
  unsigned budget = 15;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
