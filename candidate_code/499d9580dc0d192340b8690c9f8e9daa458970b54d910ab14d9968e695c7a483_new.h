// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35034792;
  double density_weight = 0.03504670;
  double prefix_weight = 0.25059770;
  double neighborhood_weight = 0.30314250;
  double late_weight = 0.12868898;
  double critical_weight = 0.11007778;
  unsigned budget = 18;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
