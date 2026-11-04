// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54975250;
  double density_weight = 0.52545330;
  double prefix_weight = 0.34980218;
  double neighborhood_weight = 0.20449133;
  double late_weight = 0.01039932;
  double critical_weight = 0.02773682;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
