// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93680921;
  double density_weight = 0.32795969;
  double prefix_weight = 0.46403579;
  double neighborhood_weight = 0.33427977;
  double late_weight = 0.01967166;
  double critical_weight = 0.22757524;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
