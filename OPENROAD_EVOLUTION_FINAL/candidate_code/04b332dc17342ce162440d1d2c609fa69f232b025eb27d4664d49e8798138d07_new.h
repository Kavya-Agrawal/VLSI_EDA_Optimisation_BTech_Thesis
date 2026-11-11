// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68550527;
  double density_weight = 0.12517899;
  double prefix_weight = 0.32567882;
  double neighborhood_weight = 0.22076309;
  double late_weight = 0.29080683;
  double critical_weight = 0.04206305;
  unsigned budget = 5;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
