// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55467256;
  double density_weight = 0.46494266;
  double prefix_weight = 0.46442193;
  double neighborhood_weight = 0.10202547;
  double late_weight = 0.05364201;
  double critical_weight = 0.37573386;
  unsigned budget = 30;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
