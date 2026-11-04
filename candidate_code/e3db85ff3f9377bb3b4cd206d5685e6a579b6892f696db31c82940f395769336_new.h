// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47955887;
  double density_weight = 0.57830869;
  double prefix_weight = 0.23936212;
  double neighborhood_weight = 0.08295233;
  double late_weight = 0.15820073;
  double critical_weight = 0.20532973;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
