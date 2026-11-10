// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99565508;
  double density_weight = 0.57106916;
  double prefix_weight = 0.46678736;
  double neighborhood_weight = 0.03758911;
  double late_weight = 0.21924781;
  double critical_weight = 0.25502215;
  unsigned budget = 37;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
