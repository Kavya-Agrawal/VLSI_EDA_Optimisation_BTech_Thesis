// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75859073;
  double density_weight = 0.26680024;
  double prefix_weight = 0.17343365;
  double neighborhood_weight = 0.01363296;
  double late_weight = 0.22571388;
  double critical_weight = 0.15265244;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
