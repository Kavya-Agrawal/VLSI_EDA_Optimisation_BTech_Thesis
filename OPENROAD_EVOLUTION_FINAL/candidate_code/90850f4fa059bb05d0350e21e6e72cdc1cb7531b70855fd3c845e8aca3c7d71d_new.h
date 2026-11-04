// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20411570;
  double density_weight = 0.50726875;
  double prefix_weight = 0.04877513;
  double neighborhood_weight = 0.03328172;
  double late_weight = 0.05927268;
  double critical_weight = 0.10737067;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
