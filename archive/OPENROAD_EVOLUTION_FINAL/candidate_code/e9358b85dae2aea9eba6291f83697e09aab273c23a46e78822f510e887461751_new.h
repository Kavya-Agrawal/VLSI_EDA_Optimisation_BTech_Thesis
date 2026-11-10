// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79298238;
  double density_weight = 0.17215527;
  double prefix_weight = 0.33107501;
  double neighborhood_weight = 0.38186107;
  double late_weight = 0.05664669;
  double critical_weight = 0.39486232;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
