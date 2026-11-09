// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61485630;
  double density_weight = 0.07801834;
  double prefix_weight = 0.42156912;
  double neighborhood_weight = 0.17790160;
  double late_weight = 0.25814848;
  double critical_weight = 0.21652559;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
