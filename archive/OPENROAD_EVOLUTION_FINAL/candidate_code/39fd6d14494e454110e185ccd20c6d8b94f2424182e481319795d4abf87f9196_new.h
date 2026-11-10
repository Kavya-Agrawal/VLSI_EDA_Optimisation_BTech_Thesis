// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67969695;
  double density_weight = 0.28407721;
  double prefix_weight = 0.48960561;
  double neighborhood_weight = 0.09223899;
  double late_weight = 0.12807740;
  double critical_weight = 0.27685632;
  unsigned budget = 28;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
