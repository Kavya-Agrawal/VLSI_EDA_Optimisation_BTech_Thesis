// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17712420;
  double density_weight = 0.13329241;
  double prefix_weight = 0.24021016;
  double neighborhood_weight = 0.08507623;
  double late_weight = 0.03630867;
  double critical_weight = 0.25029614;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
