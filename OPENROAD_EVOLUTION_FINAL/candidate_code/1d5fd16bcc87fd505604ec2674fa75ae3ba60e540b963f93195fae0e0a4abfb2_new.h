// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81010613;
  double density_weight = 0.20077018;
  double prefix_weight = 0.38294820;
  double neighborhood_weight = 0.26618120;
  double late_weight = 0.21085748;
  double critical_weight = 0.17783372;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
