// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32876728;
  double density_weight = 0.11621111;
  double prefix_weight = 0.09552107;
  double neighborhood_weight = 0.13525712;
  double late_weight = 0.24809712;
  double critical_weight = 0.07423820;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
