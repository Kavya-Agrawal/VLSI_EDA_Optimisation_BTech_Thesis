// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20034048;
  double density_weight = 0.34772887;
  double prefix_weight = 0.14926962;
  double neighborhood_weight = 0.02405747;
  double late_weight = 0.05307479;
  double critical_weight = 0.41032601;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
