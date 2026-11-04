// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17358975;
  double density_weight = 0.20447062;
  double prefix_weight = 0.32507811;
  double neighborhood_weight = 0.33168048;
  double late_weight = 0.29718070;
  double critical_weight = 0.06400165;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
