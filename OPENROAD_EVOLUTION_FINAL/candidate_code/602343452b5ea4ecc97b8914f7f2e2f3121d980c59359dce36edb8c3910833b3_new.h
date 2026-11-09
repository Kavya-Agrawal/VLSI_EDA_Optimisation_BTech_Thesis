// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38249983;
  double density_weight = 0.08807663;
  double prefix_weight = 0.29036243;
  double neighborhood_weight = 0.22047024;
  double late_weight = 0.01535707;
  double critical_weight = 0.29926518;
  unsigned budget = 22;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
