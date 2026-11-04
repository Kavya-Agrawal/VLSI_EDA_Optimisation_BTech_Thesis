// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45400745;
  double density_weight = 0.42513333;
  double prefix_weight = 0.14359308;
  double neighborhood_weight = 0.21175641;
  double late_weight = 0.04253844;
  double critical_weight = 0.41541126;
  unsigned budget = 39;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
