// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60146163;
  double density_weight = 0.38710827;
  double prefix_weight = 0.23213583;
  double neighborhood_weight = 0.38793661;
  double late_weight = 0.21236637;
  double critical_weight = 0.48666564;
  unsigned budget = 20;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
