// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07060648;
  double density_weight = 0.17694145;
  double prefix_weight = 0.30250390;
  double neighborhood_weight = 0.36088324;
  double late_weight = 0.08823145;
  double critical_weight = 0.04070541;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
