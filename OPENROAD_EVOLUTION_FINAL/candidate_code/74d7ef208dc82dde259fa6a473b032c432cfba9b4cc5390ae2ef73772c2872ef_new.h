// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44740817;
  double density_weight = 0.46891827;
  double prefix_weight = 0.02958003;
  double neighborhood_weight = 0.03553834;
  double late_weight = 0.08050246;
  double critical_weight = 0.36387345;
  unsigned budget = 14;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
