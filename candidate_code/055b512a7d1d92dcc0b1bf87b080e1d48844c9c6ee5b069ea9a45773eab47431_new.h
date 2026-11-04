// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14431513;
  double density_weight = 0.51984152;
  double prefix_weight = 0.45649620;
  double neighborhood_weight = 0.12245515;
  double late_weight = 0.11075490;
  double critical_weight = 0.14961108;
  unsigned budget = 22;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
