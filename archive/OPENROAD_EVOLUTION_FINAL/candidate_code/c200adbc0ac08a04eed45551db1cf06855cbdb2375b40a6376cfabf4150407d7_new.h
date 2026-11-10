// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36020195;
  double density_weight = 0.16129408;
  double prefix_weight = 0.42338728;
  double neighborhood_weight = 0.12421871;
  double late_weight = 0.09449695;
  double critical_weight = 0.26550702;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
